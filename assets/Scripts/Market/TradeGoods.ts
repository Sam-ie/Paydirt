import { _decorator, Component, Node, ScrollView, Label, EventTouch, Color, instantiate, Sprite, UITransform, EventMouse, EditBox } from 'cc';
const { ccclass, property } = _decorator;

// 定义 ItemData 结构体
interface ItemData {
    itemID: string; // item 的唯一标识符
    labelText: string; // item 的文本内容
}

@ccclass('TradeGoods')
export class TradeGoods extends Component {

    @property(ScrollView) // 绑定 Goods ScrollView 组件
    goodsScrollView: ScrollView = null;

    @property(ScrollView) // 绑定 Warehouse ScrollView 组件
    warehouseScrollView: ScrollView = null;

    @property(Node) // 绑定 item 预制体
    itemPrefab: Node = null;

    @property(Label) // 绑定 TradeType Label 组件
    tradeTypeLabel: Label = null;

    @property(EditBox) // 绑定 TradeNumber 输入框
    tradeNumber: EditBox = null;

    private selectedItem: Node | null = null; // 当前选中的 item
    private scrollSpeed: number = 0.03; // 滚轮滚动速度

    onLoad() {
        // 监听鼠标滚轮事件
        this.node.on(Node.EventType.MOUSE_WHEEL, this.onMouseWheel, this);
    }

    start() {
        // 初始设置 goodsScrollView 的第一个条目为选中状态
        this.selectFirstItemInGoodsScrollView();
    }

    /**
     * 选中 goodsScrollView 的第一个条目
     */
    selectFirstItemInGoodsScrollView() {
        const content = this.goodsScrollView.content;
        if (content && content.children.length > 0) {
            const firstItem = content.children[0]; // 获取第一个条目
            this.setSelectedItem(firstItem); // 设置为选中状态
        }
    }

    /**
     * 设置选中的 item
     * @param item 选中的 item 节点
     */
    setSelectedItem(item: Node) {
        // 取消之前选中的 item 的背景颜色
        if (this.selectedItem) {
            const previousBackground = this.selectedItem.getChildByName('background')?.getComponent(Sprite);
            if (previousBackground) {
                previousBackground.color = new Color(255, 255, 255, 255); // 恢复为白色
            }
        }

        // 设置当前选中的 item 的背景颜色为浅蓝色
        const currentBackground = item.getChildByName('background')?.getComponent(Sprite);
        if (currentBackground) {
            currentBackground.color = new Color(180, 180, 255, 255); // 设置为浅蓝色
        }

        // 更新当前选中的 item
        this.selectedItem = item;

        // 根据 itemID 的首字母设置 TradeType 文本
        const itemID = item['itemID'];
        if (itemID && this.tradeTypeLabel) {
            if (itemID.startsWith('g')) {
                this.tradeTypeLabel.string = '买入：';
            } else if (itemID.startsWith('w')) {
                this.tradeTypeLabel.string = '卖出：';
            }
        }

        // 将 TradeNumber 输入框置为空
        if (this.tradeNumber) {
            this.tradeNumber.string = '';
        }
    }

    /**
     * 更新 ScrollView 中的 item 内容
     * @param scrollView 目标 ScrollView 组件
     * @param items ItemData 数组，包含 itemID 和 label 文本
     */
    updateText(scrollView: ScrollView, items: ItemData[]) {
        const content = scrollView.content; // 获取 ScrollView 的内容容器
        if (content && this.itemPrefab) {
            // 清空现有内容
            content.removeAllChildren();

            // 动态添加 item
            for (let i = 0; i < items.length; i++) {
                const item = instantiate(this.itemPrefab);

                // 为 item 分配唯一 id 和 label 文本
                const itemData = items[i];
                item['itemID'] = itemData.itemID; // 设置 itemID
                item['scrollViewType'] = scrollView === this.goodsScrollView ? 'goods' : 'warehouse';

                // 获取 background 节点
                const background = item.getChildByName('background');
                if (background) {
                    // 获取 text 节点上的 Label 组件
                    const label = background.getChildByName('text')?.getComponent(Label);
                    // 获取 background 节点上的 Sprite 组件
                    const spriteBackground = background.getComponent(Sprite);

                    if (label && spriteBackground) {
                        label.string = itemData.labelText; // 设置文本内容
                        label.color = new Color(0, 0, 0, 255); // 设置文本颜色为黑色 (#000000)

                        // 设置 Sprite 的大小为固定值 (280, 36)
                        const spriteTransform = spriteBackground.node.getComponent(UITransform);
                        if (spriteTransform) {
                            spriteTransform.width = 290; // 设置宽度
                            spriteTransform.height = 36; // 设置高度
                        }

                        // 设置 Sprite 的位置与 Label 重合
                        const labelPosition = label.node.position;
                        spriteBackground.node.setPosition(5, labelPosition.y - 8);
                        label.node.setPosition(-125, labelPosition.y);

                        // 设置 Sprite 的颜色为白色
                        spriteBackground.color = new Color(255, 255, 255, 255);
                    }
                }

                item.on(Node.EventType.TOUCH_END, this.onItemSelected, this); // 绑定选中事件
                content.addChild(item);

                // 检查是否需要选中当前 item
                if (this.selectedItem && this.selectedItem['itemID'] === itemData.itemID) {
                    this.setSelectedItem(item); // 如果 itemID 匹配，则选中该 item
                }
            }

            // 强制更新 Layout 组件
            const layout = content.getComponent('cc.Layout');
            if (layout) {
                layout.updateLayout();
            }

            // 动态调整 content 的大小
            const contentTransform = content.getComponent(UITransform);
            if (contentTransform) {
                const itemHeight = 45; // 每个 item 的高度间隔
                contentTransform.height = items.length * itemHeight; // 设置 content 的总高度
            }
        }
    }

    /**
     * item 被选中时的事件
     * @param event 触摸事件
     */
    onItemSelected(event: EventTouch) {
        const item = event.target; // 获取被选中的 item 节点
        this.setSelectedItem(item); // 设置为选中状态
    }

    /**
     * 鼠标滚轮事件
     * @param event 鼠标事件
     */
    onMouseWheel(event: EventMouse) {
        // 获取鼠标位置
        const mousePosition = event.getLocation();

        // 检查鼠标是否在 Goods ScrollView 的 view 区域内
        if (this.isMouseInView(this.goodsScrollView, mousePosition)) {
            const deltaY = event.getScrollY(); // 获取滚轮垂直滚动量
            this.scrollContent(this.goodsScrollView, deltaY);
        }

        // 检查鼠标是否在 Warehouse ScrollView 的 view 区域内
        if (this.isMouseInView(this.warehouseScrollView, mousePosition)) {
            const deltaY = event.getScrollY(); // 获取滚轮垂直滚动量
            this.scrollContent(this.warehouseScrollView, deltaY);
        }
    }

    /**
     * 检查鼠标是否在 ScrollView 的 view 区域内
     * @param scrollView 目标 ScrollView
     * @param mousePosition 鼠标位置
     * @returns 是否在 view 区域内
     */
    isMouseInView(scrollView: ScrollView, mousePosition: { x: number, y: number }): boolean {
        if (!scrollView || !scrollView.node) return false;

        const viewNode = scrollView.node;
        const viewTransform = viewNode.getComponent(UITransform);
        if (!viewTransform) return false;

        // 获取 view 区域的边界
        const viewWorldPos = viewNode.worldPosition;
        const viewWidth = viewTransform.width;
        const viewHeight = viewTransform.height;

        // 检查鼠标位置是否在 view 区域内
        return (
            mousePosition.x >= viewWorldPos.x - viewWidth / 2 &&
            mousePosition.x <= viewWorldPos.x + viewWidth / 2 &&
            mousePosition.y >= viewWorldPos.y - viewHeight / 2 &&
            mousePosition.y <= viewWorldPos.y + viewHeight / 2
        );
    }

    /**
     * 滚动 ScrollView 的 content
     * @param scrollView 目标 ScrollView
     * @param deltaY 滚轮滚动量
     */
    scrollContent(scrollView: ScrollView, deltaY: number) {
        const content = scrollView.content;
        if (content) {
            const contentTransform = content.getComponent(UITransform);
            const viewTransform = scrollView.node.getComponent(UITransform);
            if (contentTransform && viewTransform) {
                // 如果 content 的高度小于 view 的高度，则不需要滚动
                if (contentTransform.height <= viewTransform.height) {
                    return;
                }

                const currentY = content.position.y;
                const newY = currentY - deltaY * this.scrollSpeed; // 根据滚轮滚动量调整 content 的位置

                // 限制 content 的移动范围
                const maxY = Math.max(viewTransform.height, contentTransform.height - 100);
                const clampedY = Math.max(100, Math.min(maxY, newY)); // 限制 Y 轴范围
                content.setPosition(content.position.x, clampedY, content.position.z);
            }
        }
    }

    /**
     * 获取选中的 item
     * @returns 返回选中的 item
     */
    getItem(): Node | null {
        return this.selectedItem;
    }
}