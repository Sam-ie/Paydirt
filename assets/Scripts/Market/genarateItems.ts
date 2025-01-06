import { _decorator, Component, Node, ScrollView } from 'cc';
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

@ccclass('genarateItems')
export class genarateItems extends Component {
    @property(ScrollView) // 绑定 Goods ScrollView 组件
    goodsScrollView: ScrollView = null;

    @property(ScrollView) // 绑定 Warehouse ScrollView 组件
    warehouseScrollView: ScrollView = null;

    private goodsList: Goods[] = []; // 商品列表

    start() {
        // 从本地存储加载商品数据
        this.loadGoodsFromLocalStorage();

        // 在 start 的最后执行一次 updateText，显示在 goodsScrollView 中
        const stringList = this.generateStringList();
        this.updateText('goods', stringList);
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
            this.goodsList = [
                new Goods('1', '商品A', 100, 95, -5, 100, 20),
                new Goods('2', '商品B', 200, 210, 5, 150, 50),
                new Goods('3', '商品C', 300, 300, 0, 200, 100),
            ];
            this.saveGoodsToLocalStorage(); // 保存默认值到本地存储
        }
    }

    /**
     * 保存商品数据到本地存储
     */
    saveGoodsToLocalStorage() {
        localStorage.setItem('goodsList', JSON.stringify(this.goodsList));
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
            const stringList = this.generateStringList();
            this.updateText(targetScrollView, stringList);
        } else {
            console.error(`商品 ID ${id} 不存在`);
        }
    }

    /**
     * 生成拼接字符串列表
     * @returns 拼接字符串列表
     */
    generateStringList(): string[] {
        return this.goodsList.map((goods) => {
            // 现价化为英文数字格式的字符串，保留两位小数
            const currentPriceStr = goods.currentPrice.toLocaleString('en-US', {
                minimumFractionDigits: 2,
                maximumFractionDigits: 2,
            });

            // 价格升降百分比化为百分数形式的字符串，保留正负号
            const priceChangePercentageStr = `${goods.priceChangePercentage.toFixed(2)}%`;

            // 参考商品数量 - 其他人占用的商品数量
            const availableQuantity = goods.referenceQuantity - goods.occupiedQuantity;

            // 拼接字符串
            return `${goods.name}, ${currentPriceStr}, ${priceChangePercentageStr}, ${availableQuantity}`;
        });
    }

    /**
     * 调用外部脚本的 updateText 方法
     * @param targetScrollView 目标 ScrollView（'goods' 或 'warehouse'）
     * @param stringList 拼接字符串列表
     */
    updateText(targetScrollView: 'goods' | 'warehouse', stringList: string[]) {
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
            tradeGoods.updateText(scrollView, stringList); // 调用 updateText 方法
        } else {
            console.error('TradeGoods 组件或 updateText 方法未找到');
        }
    }
}