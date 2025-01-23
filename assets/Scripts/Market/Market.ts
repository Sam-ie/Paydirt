// Market.ts
// Goods 类定义
export class Goods {
    id: string; // 商品 ID
    name: string; // 商品名
    referencePrice: number; // 参考价格
    currentPrice: number; // 现价
    priceChangePercentage: number; // 价格升降百分比
    referenceQuantity: number; // 参考商品数量
    occupiedQuantity: number; // 其他人占用的商品数量
    myQuantity: number; // 持有数量

    constructor(
        id: string,
        name: string,
        referencePrice: number,
        currentPrice: number,
        priceChangePercentage: number,
        referenceQuantity: number,
        occupiedQuantity: number,
        myQuantity: number = 0 // 默认值为 0
    ) {
        this.id = id;
        this.name = name;
        this.referencePrice = referencePrice;
        this.currentPrice = currentPrice;
        this.priceChangePercentage = priceChangePercentage;
        this.referenceQuantity = referenceQuantity;
        this.occupiedQuantity = occupiedQuantity;
        this.myQuantity = myQuantity;
    }
}

// Warehouse 类定义
export class Warehouse {
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

export interface ItemData {
    itemID: string; // item 的唯一标识符
    labelText: string; // item 的文本内容
}

// 默认静态 Goods 数组
export const defaultGoods: Goods[] = [
    new Goods('g1', '棒棒糖    ', 3, 3, 0, 10000, 0, 0),
    new Goods('g2', '奶茶      ', 10, 10, 0, 4000, 0, 0),
    new Goods('g3', '畅销书    ', 30, 30, 0, 1600, 0, 0),
    new Goods('g4', '运动鞋    ', 100, 100, 0, 640, 0, 0),
    new Goods('g5', '休闲外套  ', 300, 300, 0, 256, 0, 0),
    new Goods('g6', '智能手机  ', 1000, 1000, 0, 768, 0, 0),
    new Goods('g7', '笔记本电脑', 3000, 3000, 0, 307, 0, 0),
    new Goods('g8', '摩托车    ', 10000, 10000, 0, 921, 0, 0),
    new Goods('g9', '珠宝首饰  ', 30000, 30000, 0, 369, 0, 0),
    new Goods('g10', '小轿车    ', 100000, 100000, 0, 1107, 0, 0),
    new Goods('g11', '豪华轿车  ', 300000, 300000, 0, 443, 0, 0),
    new Goods('g12', '小户型公寓', 1000000, 1000000, 0, 1329, 0, 0),
    new Goods('g13', '电动超跑  ', 3000000, 3000000, 0, 532, 0, 0),
    new Goods('g14', '豪华别墅  ', 10000000, 10000000, 0, 1596, 0, 0),
    new Goods('g15', '私人飞机  ', 30000000, 30000000, 0, 639, 0, 0),
    new Goods('g16', '豪华游艇  ', 100000000, 100000000, 0, 1917, 0, 0),
    new Goods('g17', '私人岛屿  ', 300000000, 300000000, 0, 767, 0, 0),
];

// 商品列表
export let goodsList: Goods[] = [];

// 仓库列表
export let warehouseList: Warehouse[] = [];

// 从本地存储加载商品数据
export function loadGoodsFromLocalStorage() {
    const goodsData = localStorage.getItem('goodsList');
    if (goodsData) {
        goodsList = JSON.parse(goodsData).map(
            (item: any) =>
                new Goods(
                    item.id,
                    item.name,
                    item.referencePrice,
                    item.currentPrice,
                    item.priceChangePercentage,
                    item.referenceQuantity,
                    item.occupiedQuantity,
                    item.myQuantity
                )
        );
    } else {
        // 取前五项，并对这五个条目执行一次 initializeNewGoods
        goodsList = defaultGoods.slice(0, 5).map((goods) => {
            const newGoods = new Goods(
                goods.id,
                goods.name,
                goods.referencePrice,
                goods.currentPrice,
                goods.priceChangePercentage,
                goods.referenceQuantity,
                goods.occupiedQuantity,
                goods.myQuantity 
            );
            initializeNewGoods(newGoods); // 对新商品进行初始化
            return newGoods;
        });
        saveGoodsToLocalStorage();
    }
}

// 从本地存储加载仓库数据
export function loadWarehouseFromLocalStorage() {
    const warehouseData = localStorage.getItem('warehouseList');
    if (warehouseData) {
        warehouseList = JSON.parse(warehouseData).map(
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
        warehouseList = [];
        saveWarehouseToLocalStorage();
    }
}

// 保存商品数据到本地存储
export function saveGoodsToLocalStorage() {
    localStorage.setItem('goodsList', JSON.stringify(goodsList));
}

// 保存仓库数据到本地存储
export function saveWarehouseToLocalStorage() {
    localStorage.setItem('warehouseList', JSON.stringify(warehouseList));
}

// 更新商品属性
export function updateGoods(id: string, updatedGoods: Partial<Goods>) {
    const goods = goodsList.find((item) => item.id === id);
    if (goods) {
        Object.assign(goods, updatedGoods);
        saveGoodsToLocalStorage();
    } else {
        console.error(`商品 ID ${id} 不存在`);
    }
}

// 更新仓库属性
export function updateWarehouse(id: string, updatedWarehouse: Partial<Warehouse>) {
    let warehouse = warehouseList.find((item) => item.id === id);
    if (warehouse) {
        if (updatedWarehouse.quantity === 0) {
            warehouseList = warehouseList.filter((item) => item.id !== id);
        } else {
            Object.assign(warehouse, updatedWarehouse);
        }
    } else {
        warehouseList.push(new Warehouse(
            updatedWarehouse.id || '',
            updatedWarehouse.name || '',
            updatedWarehouse.averagePrice || 0,
            updatedWarehouse.priceChangePercentage || 0,
            updatedWarehouse.quantity || 0
        ));
    }
    saveWarehouseToLocalStorage();
}

/**
 * 时间流逝，更新 goodsList 和 warehouseList
 */
export function timePass() {
    goodsList.forEach((goods) => {
        goods.priceChangePercentage = parseFloat((Math.random() * (42.86 + 30) - 30).toFixed(2));
        goods.currentPrice = parseFloat((goods.referencePrice * (1 + goods.priceChangePercentage / 100)).toFixed(2));
        const rate = parseFloat((Math.random() * 40 - 20).toFixed(2));
        const ratio = Math.min(Math.max((50 + goods.priceChangePercentage + rate) / 100, 0), 1);
        goods.occupiedQuantity = Math.round(goods.referenceQuantity * ratio);
        goods.occupiedQuantity = Math.min(goods.occupiedQuantity, goods.referenceQuantity - goods.myQuantity);
    });

    warehouseList.forEach((warehouse) => {
        const goods = goodsList.find((g) => g.id.slice(1) === warehouse.id.slice(1));
        if (goods) {
            warehouse.priceChangePercentage = parseFloat(((warehouse.averagePrice / goods.currentPrice - 1) * 100).toFixed(2));
        }
    });

    saveGoodsToLocalStorage();
    saveWarehouseToLocalStorage();
}

/**
 * 对新添加的商品进行一次初始化
 * @param goods 新添加的商品
 */
export function initializeNewGoods(goods: Goods) {
    goods.priceChangePercentage = parseFloat((Math.random() * (42.86 + 30) - 30).toFixed(2));
    goods.currentPrice = parseFloat((goods.referencePrice * (1 + goods.priceChangePercentage / 100)).toFixed(2));
    const rate = parseFloat((Math.random() * 40 - 20).toFixed(2));
    const ratio = Math.min(Math.max((50 + goods.priceChangePercentage + rate) / 100, 0), 1);
    goods.occupiedQuantity = Math.round(goods.referenceQuantity * ratio);
}