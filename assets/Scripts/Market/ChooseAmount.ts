import { _decorator, Component, Node, EditBox, Button, EventTouch } from 'cc';
import { Goods, Warehouse, goodsList, warehouseList, saveGoodsToLocalStorage, saveWarehouseToLocalStorage } from './Market';
const { ccclass, property } = _decorator;

@ccclass('ChooseAmount')
export class ChooseAmount extends Component {
    @property(Node) // 绑定 SelectNumber 节点
    selectNumber: Node = null;

    @property(Node) // 绑定 GenerateItems 节点
    generateItemsNode: Node = null;

    private tradeNumber: EditBox | null = null; // TradeNumber 输入框
    private btn1: Node | null = null; // btn-1 按钮
    private btn10: Node | null = null; // btn-10 按钮
    private btnMax: Node | null = null; // btnMax 按钮
    private enterBtn: Node | null = null; // enter 按钮

    private currentItem: any = null; // 当前选中的 item

    start() {
        // 获取 TradeNumber 输入框
        this.tradeNumber = this.selectNumber.getChildByName('TradeNumber')?.getComponent(EditBox);
        if (!this.tradeNumber) {
            console.error('TradeNumber 输入框未找到');
            return;
        }

        // 获取按钮节点
        this.btn1 = this.selectNumber.getChildByName('btn-1');
        this.btn10 = this.selectNumber.getChildByName('btn-10');
        this.btnMax = this.selectNumber.getChildByName('btnMax');
        this.enterBtn = this.selectNumber.getChildByName('enter');

        if (!this.btn1 || !this.btn10 || !this.btnMax || !this.enterBtn) {
            console.error('按钮未找到');
            return;
        }

        // 绑定按钮事件
        this.bindButtonEvents(this.btn1, this.onBtn1TouchEnd.bind(this));
        this.bindButtonEvents(this.btn10, this.onBtn10TouchEnd.bind(this));
        this.bindButtonEvents(this.btnMax, this.onBtnMaxTouchEnd.bind(this));
        this.bindButtonEvents(this.enterBtn, this.onEnterTouchEnd.bind(this));

        // 绑定 TradeNumber 输入事件
        this.tradeNumber.node.on('editing-did-ended', this.onTradeNumberChanged, this);

        this.getCurrentItem();
    }

    /**
     * 绑定按钮的触摸事件
     * @param buttonNode 按钮节点
     * @param onTouchEnd 触摸结束的回调函数
     */
    bindButtonEvents(buttonNode: Node, onTouchEnd: (event: EventTouch) => void) {
        if (!buttonNode) return;

        buttonNode.on(Node.EventType.TOUCH_START, () => {
            // 触摸开始，无需日志
        });

        buttonNode.on(Node.EventType.TOUCH_END, onTouchEnd);

        buttonNode.on(Node.EventType.TOUCH_CANCEL, () => {
            // 触摸取消，无需日志
        });
    }

    /**
     * 获取当前选中的 item
     */
    getCurrentItem() {
        const marketController = this.generateItemsNode.getComponent('MarketController');
        if (marketController) {
            this.currentItem = marketController.getSelectedItemData();
        } else {
            console.error('MarketController 组件未找到');
        }
    }

    /**
     * 检查 TradeNumber 的数字边界
     */
    checkTradeNumberBoundary() {
        if (!this.tradeNumber || !this.currentItem) return;

        let value = parseInt(this.tradeNumber.string, 10);
        if (isNaN(value)) {
            value = 0; // 如果 TradeNumber 为空，按 0 处理
        }

        let maxValue = 0;
        if (this.currentItem.id.startsWith('g')) {
            // Goods 类
            maxValue = this.currentItem.referenceQuantity - this.currentItem.occupiedQuantity - this.currentItem.myQuantity;
        } else if (this.currentItem.id.startsWith('w')) {
            // Warehouse 类
            maxValue = this.currentItem.quantity;
        }

        // 限制 TradeNumber 的值在 0 到 maxValue 之间
        value = Math.max(0, Math.min(maxValue, value));

        // 更新 TradeNumber 的文本
        this.tradeNumber.string = value.toString();
    }

    /**
     * TradeNumber 输入框内容改变事件
     */
    onTradeNumberChanged() {
        if (!this.tradeNumber) return;

        // 只接受 0-9 的字符
        const newValue = this.tradeNumber.string.replace(/[^0-9]/g, '');
        this.tradeNumber.string = newValue;

        // 检查数字边界
        this.checkTradeNumberBoundary();
    }

    /**
     * btn-1 触摸结束事件
     */
    onBtn1TouchEnd(event: EventTouch) {
        if (!this.tradeNumber) return;
        this.getCurrentItem();

        let value = parseInt(this.tradeNumber.string, 10);
        if (isNaN(value)) {
            value = 0;
        }

        value = Math.max(0, value - 1); // 不能小于 0
        this.tradeNumber.string = value.toString();

        // 检查数字边界
        this.checkTradeNumberBoundary();
    }

    /**
     * btn-10 触摸结束事件
     */
    onBtn10TouchEnd(event: EventTouch) {
        if (!this.tradeNumber) return;
        this.getCurrentItem();

        let value = parseInt(this.tradeNumber.string, 10);
        if (isNaN(value)) {
            value = 0;
        }

        value = Math.max(0, value - 10); // 不能小于 0
        this.tradeNumber.string = value.toString();

        // 检查数字边界
        this.checkTradeNumberBoundary();
    }

    /**
     * btnMax 触摸结束事件
     */
    onBtnMaxTouchEnd(event: EventTouch) {
        if (!this.tradeNumber || !this.currentItem) return;
        this.getCurrentItem();

        let maxValue = 0;
        if (this.currentItem.id.startsWith('g')) {
            // Goods 类
            maxValue = this.currentItem.referenceQuantity - this.currentItem.occupiedQuantity - this.currentItem.myQuantity;
        } else if (this.currentItem.id.startsWith('w')) {
            // Warehouse 类
            maxValue = this.currentItem.quantity;
        }

        this.tradeNumber.string = maxValue.toString();
    }

    /**
     * enter 触摸结束事件
     */
    onEnterTouchEnd(event: EventTouch) {
        if (!this.tradeNumber || !this.currentItem) return;
        this.getCurrentItem();

        const value = parseInt(this.tradeNumber.string, 10);
        if (isNaN(value)) {
            return;
        }

        if (this.currentItem.id.startsWith('g')) {
            // 选中 Goods 条目
            this.currentItem.myQuantity += value; // 增加 myQuantity

            // 将 Goods 的 id 首字母 g 替换为 w，生成 Warehouse 的 id
            const warehouseId = 'w' + this.currentItem.id.slice(1);

            // 查找对应的 Warehouse 条目
            const warehouseItem = warehouseList.find((item) => item.id === warehouseId);
            if (warehouseItem) {
                warehouseItem.quantity += value; // 增加 Warehouse 的 quantity
            } else {
                // 如果 Warehouse 中没有对应条目，则创建新条目
                warehouseList.push(new Warehouse(
                    warehouseId, // 使用转换后的 id
                    this.currentItem.name,
                    this.currentItem.currentPrice, // 使用当前价格作为平均价格
                    0, // 初始价格变化百分比为 0
                    value // 初始数量为 TradeNumber 的值
                ));
            }
        } else if (this.currentItem.id.startsWith('w')) {
            // 选中 Warehouse 条目
            this.currentItem.quantity -= value; // 减少 Warehouse 的 quantity

            // 如果 quantity 减去 value 后为 0，则删除该 Warehouse 条目
            if (this.currentItem.quantity === 0) {
                const index = warehouseList.findIndex((item) => item.id === this.currentItem.id);
                if (index !== -1) {
                    warehouseList.splice(index, 1); // 从数组中删除该条目
                }
            }

            // 将 Warehouse 的 id 首字母 w 替换为 g，生成 Goods 的 id
            const goodsId = 'g' + this.currentItem.id.slice(1);

            // 查找对应的 Goods 条目
            const goodsItem = goodsList.find((item) => item.id === goodsId);
            if (goodsItem) {
                goodsItem.myQuantity -= value; // 减少 Goods 的 myQuantity
            }
        }

        // 保存更新后的数据到本地存储
        saveGoodsToLocalStorage();
        saveWarehouseToLocalStorage();

        // 更新显示
        const marketController = this.generateItemsNode.getComponent('MarketController');
        if (marketController) {
            const goodsStringList = marketController.generateGoodsStringList();
            const warehouseStringList = marketController.generateWarehouseStringList();
            marketController.updateText('goods', goodsStringList);
            marketController.updateText('warehouse', warehouseStringList);
        }
    }
}