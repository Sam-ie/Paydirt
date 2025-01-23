// MarketController.ts
import { _decorator, Component, ScrollView, director } from 'cc';
import { Paydirt } from '../Select/Paydirt';
import EventConstants from '../Startup/EventConstants'; // 导入全局事件名称
const { ccclass, property } = _decorator;

import { Goods, Warehouse, defaultGoods, goodsList, warehouseList, loadGoodsFromLocalStorage, loadWarehouseFromLocalStorage, timePass, saveGoodsToLocalStorage, ItemData, initializeNewGoods } from './Market'; // 导入 Market 模块

@ccclass('MarketController')
export class MarketController extends Component {
    // 单例实例
    private static instance: MarketController;

    @property(ScrollView) // 绑定 Goods ScrollView 组件
    goodsScrollView: ScrollView = null;

    @property(ScrollView) // 绑定 Warehouse ScrollView 组件
    warehouseScrollView: ScrollView = null;

    public level: number = 1; // 公有 level 变量
    private paydirt: Paydirt;

    // 设置单例实例
    public static setInstance(instance: MarketController) {
        MarketController.instance = instance;
    }

    // 获取单例实例
    public static getInstance(): MarketController {
        return MarketController.instance;
    }

    onLoad() {
        // 设置单例实例
        MarketController.instance = this;

        // 获取 Paydirt 实例
        this.paydirt = Paydirt.getInstance();


        // 从本地存储加载商品数据
        loadGoodsFromLocalStorage();

        // 从本地存储加载仓库数据
        loadWarehouseFromLocalStorage();

        // 在 start 的最后执行一次 updateText，显示在 goodsScrollView 和 warehouseScrollView 中
        const goodsStringList = this.generateGoodsStringList();
        const warehouseStringList = this.generateWarehouseStringList();
        this.updateText('goods', goodsStringList);
        this.updateText('warehouse', warehouseStringList);
    }

    start() {
        // 删除所有本地存储变量
        //localStorage.clear();
    }

    /**
     * 增加 level 并添加新的 Goods
     */
    public addLevel() {
        this.level += 1; // level 加 1

        // 添加静态数组的第 5 + 2 * level - 3 和 5 + 2 * level - 2 项
        const newGoods1 = defaultGoods[5 + 2 * this.level - 4]; // 5 + 2 * level - 3
        const newGoods2 = defaultGoods[5 + 2 * this.level - 3]; // 5 + 2 * level - 2

        if (newGoods1 && newGoods2) {
            // 对新添加的商品进行一次类似 timePass 的操作
            initializeNewGoods(newGoods1);
            initializeNewGoods(newGoods2);

            goodsList.push(newGoods1, newGoods2); // 同时添加两项
            saveGoodsToLocalStorage(); // 保存到本地存储

            // 生成拼接字符串列表并调用 updateText
            const stringList = this.generateGoodsStringList();
            this.updateText('goods', stringList);
        } else {
            console.error('没有更多的默认商品可以添加');
        }
    }

    /**
     * 生成商品拼接字符串列表
     * @returns 拼接字符串列表
     */
    generateGoodsStringList(): ItemData[] {
        return goodsList
            .filter((goods) => goods.referenceQuantity - goods.occupiedQuantity - goods.myQuantity !== 0) // 过滤掉 availableQuantity 为 0 的商品
            .map((goods) => {
                const currentPriceStr = goods.currentPrice.toLocaleString('en-US', {
                    minimumFractionDigits: 2,
                    maximumFractionDigits: 2,
                }).padStart(14, ' ');

                const priceChangePercentageStr = `${goods.priceChangePercentage.toFixed(1)}%`.padStart(7, ' ');

                const availableQuantity = (goods.referenceQuantity - goods.occupiedQuantity - goods.myQuantity).toString().padStart(8, ' '); // 更新 availableQuantity 计算逻辑

                const labelText = `${goods.name}${currentPriceStr}${priceChangePercentageStr}${availableQuantity}`;

                return {
                    itemID: goods.id,
                    labelText: labelText,
                };
            });
    }

    /**
     * 生成仓库拼接字符串列表
     * @returns 拼接字符串列表
     */
    generateWarehouseStringList(): ItemData[] {
        return warehouseList.map((warehouse) => {
            const averagePriceStr = warehouse.averagePrice.toLocaleString('en-US', {
                minimumFractionDigits: 2,
                maximumFractionDigits: 2,
            }).padStart(14, '    ');

            const priceChangePercentageStr = `${warehouse.priceChangePercentage.toFixed(1)}%`.padStart(7, ' ');

            const quantityStr = warehouse.quantity.toString().padStart(8, ' ');

            const labelText = `${warehouse.name}${averagePriceStr}${priceChangePercentageStr}${quantityStr}`;

            return {
                itemID: warehouse.id,
                labelText: labelText,
            };
        });
    }

    /**
     * 调用外部脚本的 updateText 方法
     * @param targetScrollView 目标 ScrollView（'goods' 或 'warehouse'）
     * @param itemDataList ItemData 列表
     */
    updateText(targetScrollView: 'goods' | 'warehouse', itemDataList: ItemData[]) {
        let scrollView: ScrollView | null = null;

        if (targetScrollView === 'goods') {
            scrollView = this.goodsScrollView;
        } else if (targetScrollView === 'warehouse') {
            scrollView = this.warehouseScrollView;
        }

        if (!scrollView) {
            return;
        }

        const tradeGoods = this.node.getComponent('TradeGoods');
        if (tradeGoods && tradeGoods.updateText) {
            tradeGoods.updateText(scrollView, itemDataList);
        } else {
            console.error('TradeGoods 组件或 updateText 方法未找到');
        }
    }

    /**
     * 获取选中的 item 对应的 Goods 或 Warehouse 实例
     * @returns Goods 或 Warehouse 实例，如果未选中则返回 null
     */
    getSelectedItemData(): Goods | Warehouse | null {
        const tradeGoods = this.node.getComponent('TradeGoods');
        if (!tradeGoods) {
            console.error('TradeGoods 组件未找到');
            return null;
        }

        const selectedItem = tradeGoods.getItem();
        if (!selectedItem) {
            console.log('未选中任何 item');
            return null;
        }

        const itemID = selectedItem['itemID'];
        if (!itemID) {
            console.error('选中的 item 没有 itemID');
            return null;
        }
        if (itemID.startsWith('g')) {
            const goods = goodsList.find((item) => item.id === itemID);
            return goods || null;
        } else if (itemID.startsWith('w')) {
            const warehouse = warehouseList.find((item) => item.id === itemID);
            return warehouse || null;
        }

        console.error(`未知的 itemID 前缀: ${itemID}`);
        return null;
    }

    /**
     * 时间流逝，更新 goodsList 和 warehouseList
     */
    public timePass() {
        // 调用 Market 的 timePass 方法
        timePass();

        // 更新显示
        const goodsStringList = this.generateGoodsStringList();
        const warehouseStringList = this.generateWarehouseStringList();
        this.updateText('goods', goodsStringList);
        this.updateText('warehouse', warehouseStringList);
    }
}