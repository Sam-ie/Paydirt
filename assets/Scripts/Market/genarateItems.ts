import { _decorator, Component, Node, ScrollView, director } from 'cc';
import EventConstants from '../Startup/EventConstants'; // 导入全局事件名称
const { ccclass, property } = _decorator;

// Goods 类定义
class Goods {
    id: string; // 商品 ID
    name: string; // 商品名
    referencePrice: number; // 参考价格
    currentPrice: number; // 现价
    priceChangePercentage: number; // 价格升降百分比
    referenceQuantity: number; // 参考商品数量
    occupiedQuantity: number; // 其他人占用的商品数量

    constructor(
        id: string,
        name: string,
        referencePrice: number,
        currentPrice: number,
        priceChangePercentage: number,
        referenceQuantity: number,
        occupiedQuantity: number
    ) {
        this.id = id;
        this.name = name;
        this.referencePrice = referencePrice;
        this.currentPrice = currentPrice;
        this.priceChangePercentage = priceChangePercentage;
        this.referenceQuantity = referenceQuantity;
        this.occupiedQuantity = occupiedQuantity;
    }
}

// Warehouse 类定义
class Warehouse {
    id: string; // 商品 ID
    name: string; // 商品名
    averagePrice: number; // 平均价格
    priceChangePercentage: number; // 价格升降百分比
    quantity: number; // 持有数量

    constructor(
        id: string,
        name: string,
        averagePrice: number,
        priceChangePercentage: number,
        quantity: number
    ) {
        this.id = id;
        this.name = name;
        this.averagePrice = averagePrice;
        this.priceChangePercentage = priceChangePercentage;
        this.quantity = quantity;
    }
}

// ItemData 结构体
interface ItemData {
    itemID: string; // item 的唯一标识符
    labelText: string; // item 的文本内容
}

@ccclass('GenarateItems')
export class GenarateItems extends Component {
    @property(ScrollView) // 绑定 Goods ScrollView 组件
    goodsScrollView: ScrollView = null;

    @property(ScrollView) // 绑定 Warehouse ScrollView 组件
    warehouseScrollView: ScrollView = null;

    public level: number = 1; // 公有 level 变量

    private goodsList: Goods[] = []; // 商品列表
    private warehouseList: Warehouse[] = []; // 仓库列表

    // 默认静态 Goods 数组
    private static defaultGoods: Goods[] = [
        new Goods('g1', '棒棒糖    ', 3, 3, 0, 10000, 0),
        new Goods('g2', '奶茶      ', 10, 10, 0, 4000, 0),
        new Goods('g3', '畅销书    ', 30, 30, 0, 1600, 0),
        new Goods('g4', '运动鞋    ', 100, 100, 0, 640, 0),
        new Goods('g5', '休闲外套  ', 300, 300, 0, 256, 0),
        new Goods('g6', '智能手机  ', 1000, 1000, 0, 768, 0),
        new Goods('g7', '笔记本电脑', 3000, 3000, 0, 307, 0),
        new Goods('g8', '摩托车    ', 10000, 10000, 0, 921, 0),
        new Goods('g9', '珠宝首饰  ', 30000, 30000, 0, 369, 0),
        new Goods('g10', '小轿车    ', 100000, 100000, 0, 1107, 0),
        new Goods('g11', '豪华轿车  ', 300000, 300000, 0, 443, 0),
        new Goods('g12', '小户型公寓', 1000000, 1000000, 0, 1329, 0),
        new Goods('g13', '电动超跑  ', 3000000, 3000000, 0, 532, 0),
        new Goods('g14', '豪华别墅  ', 10000000, 10000000, 0, 1596, 0),
        new Goods('g15', '私人飞机  ', 30000000, 30000000, 0, 639, 0),
        new Goods('g16', '豪华游艇  ', 100000000, 100000000, 0, 1917, 0),
        new Goods('g17', '私人岛屿  ', 300000000, 300000000, 0, 767, 0),
    ];

    start() {
        // 删除所有本地存储变量
        localStorage.clear();

        // 从本地存储加载商品数据
        this.loadGoodsFromLocalStorage();

        // 从本地存储加载仓库数据
        this.loadWarehouseFromLocalStorage();

        // 在 start 的最后执行一次 updateText，显示在 goodsScrollView 和 warehouseScrollView 中
        const goodsStringList = this.generateGoodsStringList();
        const warehouseStringList = this.generateWarehouseStringList();
        this.updateText('goods', goodsStringList);
        this.updateText('warehouse', warehouseStringList);

        this.timePass();
        // 监听时间跳跃事件
        director.on(EventConstants.TIME_JUMP_EVENT, this.timePass, this);
    }

    onDestroy() {
        // 移除事件监听
        director.off(EventConstants.TIME_JUMP_EVENT, this.timePass, this);
    }

    /**
     * 增加 level 并添加新的 Goods
     */
    public addLevel() {
        this.level += 1; // level 加 1

        // 添加静态数组的第 5 + 2 * level - 3 和 5 + 2 * level - 2 项
        const newGoods1 = GenarateItems.defaultGoods[5 + 2 * this.level - 4]; // 5 + 2 * level - 3
        const newGoods2 = GenarateItems.defaultGoods[5 + 2 * this.level - 3]; // 5 + 2 * level - 2

        if (newGoods1 && newGoods2) {
            this.goodsList.push(newGoods1, newGoods2); // 同时添加两项
            this.saveGoodsToLocalStorage(); // 保存到本地存储

            // 生成拼接字符串列表并调用 updateText
            const stringList = this.generateGoodsStringList();
            this.updateText('goods', stringList);
        } else {
            console.error('没有更多的默认商品可以添加');
        }
    }

    /**
     * 从本地存储加载商品数据
     */
    loadGoodsFromLocalStorage() {
        const goodsData = localStorage.getItem('goodsList');
        if (goodsData) {
            // 如果本地存储有数据，则解析为 Goods 数组
            this.goodsList = JSON.parse(goodsData).map(
                (item: any) =>
                    new Goods(
                        item.id,
                        item.name,
                        item.referencePrice,
                        item.currentPrice,
                        item.priceChangePercentage,
                        item.referenceQuantity,
                        item.occupiedQuantity
                    )
            );
        } else {
            // 如果本地存储没有数据，则设置为默认值
            this.goodsList = GenarateItems.defaultGoods.slice(0, 5); // 取前五项
            this.saveGoodsToLocalStorage(); // 保存默认值到本地存储
        }
    }

    /**
     * 从本地存储加载仓库数据
     */
    loadWarehouseFromLocalStorage() {
        const warehouseData = localStorage.getItem('warehouseList');
        if (warehouseData) {
            // 如果本地存储有数据，则解析为 Warehouse 数组
            this.warehouseList = JSON.parse(warehouseData).map(
                (item: any) =>
                    new Warehouse(
                        item.id,
                        item.name,
                        item.averagePrice,
                        item.priceChangePercentage,
                        item.quantity
                    )
            );
        } else {
            // 如果本地存储没有数据，则设置为空
            this.warehouseList = [];
            this.saveWarehouseToLocalStorage(); // 保存默认值到本地存储
        }
    }

    /**
     * 保存商品数据到本地存储
     */
    saveGoodsToLocalStorage() {
        localStorage.setItem('goodsList', JSON.stringify(this.goodsList));
    }

    /**
     * 保存仓库数据到本地存储
     */
    saveWarehouseToLocalStorage() {
        localStorage.setItem('warehouseList', JSON.stringify(this.warehouseList));
    }

    /**
     * 更新商品属性
     * @param id 商品 ID
     * @param updatedGoods 更新的商品属性
     * @param targetScrollView 目标 ScrollView（'goods' 或 'warehouse'）
     */
    updateGoods(id: string, updatedGoods: Partial<Goods>, targetScrollView: 'goods' | 'warehouse') {
        const goods = this.goodsList.find((item) => item.id === id);
        if (goods) {
            // 更新商品属性
            Object.assign(goods, updatedGoods);
            this.saveGoodsToLocalStorage(); // 保存到本地存储

            // 生成拼接字符串列表并调用 updateText
            const stringList = this.generateGoodsStringList();
            this.updateText(targetScrollView, stringList);
        } else {
            console.error(`商品 ID ${id} 不存在`);
        }
    }

    /**
     * 更新仓库属性
     * @param id 商品 ID
     * @param updatedWarehouse 更新的仓库属性
     * @param targetScrollView 目标 ScrollView（'goods' 或 'warehouse'）
     */
    updateWarehouse(id: string, updatedWarehouse: Partial<Warehouse>, targetScrollView: 'goods' | 'warehouse') {
        let warehouse = this.warehouseList.find((item) => item.id === id);

        if (warehouse) {
            // 如果现有 id 的 item 的 quantity 为 0，直接删除这条 item
            if (updatedWarehouse.quantity === 0) {
                this.warehouseList = this.warehouseList.filter((item) => item.id !== id);
            } else {
                // 更新仓库属性
                Object.assign(warehouse, updatedWarehouse);
            }
        } else {
            // 如果输入的 id 不在现有 id 内，则在 Warehouse 最后新建一条 item
            this.warehouseList.push(warehouse);
        }

        this.saveWarehouseToLocalStorage(); // 保存到本地存储

        // 生成拼接字符串列表并调用 updateText
        const stringList = this.generateWarehouseStringList();
        this.updateText(targetScrollView, stringList);
    }

    /**
 * 生成商品拼接字符串列表
 * @returns 拼接字符串列表
 */
    generateGoodsStringList(): ItemData[] {
        return this.goodsList
            .filter((goods) => goods.referenceQuantity - goods.occupiedQuantity !== 0) // 过滤掉 availableQuantity 为 0 的商品
            .map((goods) => {
                // 现价化为英文数字格式的字符串，保留两位小数
                const currentPriceStr = goods.currentPrice.toLocaleString('en-US', {
                    minimumFractionDigits: 2,
                    maximumFractionDigits: 2,
                }).padStart(14, ' '); // 不足 14 个字符的，前补空格

                // 价格升降百分比化为百分数形式的字符串，保留正负号
                const priceChangePercentageStr = `${goods.priceChangePercentage.toFixed(1)}%`.padStart(7, ' '); // 不足 7 个字符的，前补空格

                // 参考商品数量 - 其他人占用的商品数量
                const availableQuantity = (goods.referenceQuantity - goods.occupiedQuantity).toString().padStart(8, ' '); // 不足 8 个字符的，前补空格

                // 拼接字符串，每项中间用空格连接
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
        return this.warehouseList.map((warehouse) => {
            // 平均价格化为英文数字格式的字符串，保留两位小数
            const averagePriceStr = warehouse.averagePrice.toLocaleString('en-US', {
                minimumFractionDigits: 2,
                maximumFractionDigits: 2,
            }).padStart(14, '    '); // 不足 14 个字符的，前补空格

            // 价格升降百分比化为百分数形式的字符串，保留正负号
            const priceChangePercentageStr = `${warehouse.priceChangePercentage.toFixed(1)}%`.padStart(7, ' '); // 不足 7 个字符的，前补空格

            // 持有数量
            const quantityStr = warehouse.quantity.toString().padStart(8, ' '); // 不足 8 个字符的，前补空格

            // 拼接字符串
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

        // 根据目标 ScrollView 选择对应的 ScrollView 组件
        if (targetScrollView === 'goods') {
            scrollView = this.goodsScrollView;
        } else if (targetScrollView === 'warehouse') {
            scrollView = this.warehouseScrollView;
        }

        if (!scrollView) {
            console.error('目标 ScrollView 未绑定');
            return;
        }

        // 获取 TradeGoods 组件
        const tradeGoods = this.node.getComponent('TradeGoods');
        if (tradeGoods && tradeGoods.updateText) {
            tradeGoods.updateText(scrollView, itemDataList); // 调用 updateText 方法
        } else {
            console.error('TradeGoods 组件或 updateText 方法未找到');
        }
    }

    /**
     * 获取选中的 item 对应的 Goods 或 Warehouse 实例
     * @returns Goods 或 Warehouse 实例，如果未选中则返回 null
     */
    getSelectedItemData(): Goods | Warehouse | null {
        // 获取 TradeGoods 组件
        const tradeGoods = this.node.getComponent('TradeGoods');
        if (!tradeGoods) {
            console.error('TradeGoods 组件未找到');
            return null;
        }

        // 获取选中的 item
        const selectedItem = tradeGoods.getItem();
        if (!selectedItem) {
            console.log('未选中任何 item');
            return null;
        }

        // 获取 itemID
        const itemID = selectedItem['itemID'];
        if (!itemID) {
            console.error('选中的 item 没有 itemID');
            return null;
        }

        // 根据 itemID 查找对应的 Goods 或 Warehouse 实例
        if (itemID.startsWith('g')) {
            const goods = this.goodsList.find((item) => item.id === itemID);
            return goods || null;
        } else if (itemID.startsWith('w')) {
            const warehouse = this.warehouseList.find((item) => item.id === itemID);
            return warehouse || null;
        }

        console.error(`未知的 itemID 前缀: ${itemID}`);
        return null;
    }


    /**
 * 生成指定范围内的随机数
 * @param min 最小值
 * @param max 最大值
 * @returns 随机数
 */
    private getRandomNumber(min: number, max: number): number {
        return Math.random() * (max - min) + min;
    }

    /**
     * 限制数值在指定范围内
     * @param value 输入值
     * @param min 最小值
     * @param max 最大值
     * @returns 限制后的值
     */
    private clamp(value: number, min: number, max: number): number {
        return Math.min(Math.max(value, min), max);
    }

    /**
     * 时间流逝，更新 goodsList 和 warehouseList
     */
    private timePass() {
        // 更新 goodsList
        this.goodsList.forEach((goods) => {
            // 生成 priceChangePercentage（范围 -30.00 到 42.86 的随机数）
            goods.priceChangePercentage = parseFloat(this.getRandomNumber(-30.00, 42.86).toFixed(2));

            // 更新 currentPrice
            goods.currentPrice = parseFloat((goods.referencePrice * (1 + goods.priceChangePercentage / 100)).toFixed(2));

            // 生成 rate（范围 -20 到 20 的随机数）
            const rate = parseFloat(this.getRandomNumber(-20.00, 20.00).toFixed(2))

            // 计算 occupiedQuantity 的比例（限制在 0 到 1 之间）
            const ratio = this.clamp((50 + goods.priceChangePercentage + rate) / 100, 0, 1);

            // 更新 occupiedQuantity（四舍五入）
            goods.occupiedQuantity = Math.round(goods.referenceQuantity * ratio);
        });

        // 更新 warehouseList
        this.warehouseList.forEach((warehouse) => {
            // 在 goodsList 中查找 id 数字部分相同的项
            const goods = this.goodsList.find((g) => g.id.slice(1) === warehouse.id.slice(1));

            if (goods) {
                // 更新 priceChangePercentage
                warehouse.priceChangePercentage = parseFloat(((warehouse.averagePrice / goods.currentPrice - 1) * 100).toFixed(2));
            }
        });

        // 保存更新后的数据到本地存储
        this.saveGoodsToLocalStorage();
        this.saveWarehouseToLocalStorage();

        // 更新显示
        const goodsStringList = this.generateGoodsStringList();
        const warehouseStringList = this.generateWarehouseStringList();
        this.updateText('goods', goodsStringList);
        this.updateText('warehouse', warehouseStringList);
    }
}