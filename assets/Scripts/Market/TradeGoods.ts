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
    private isDragging: boolean = false; // 是否正在拖动
    private lastMousePosition: { x: number, y: number } = { x: 0, y: 0 }; // 上一次鼠标位置
    private isBarDragging: boolean = false; // 是否正在拖动 bar
    private currentScrollView: ScrollView | null = null; // 当前操作的 ScrollView
    private currentScrollbar: Node | null = null; // 当前拖动的 scrollbar
    private currentBar: Node | null = null; // 当前拖动的 bar

    onLoad() {
        // 监听鼠标滚轮事件
        this.node.on(Node.EventType.MOUSE_WHEEL, this.onMouseWheel, this);

        // 监听鼠标按下事件
        this.node.on(Node.EventType.MOUSE_DOWN, this.onMouseDown, this);

        // 监听鼠标移动事件
        this.node.on(Node.EventType.MOUSE_MOVE, this.onMouseMove, this);

        // 监听鼠标松开事件
        this.node.on(Node.EventType.MOUSE_UP, this.onMouseUp, this);

        // 绑定 Goods ScrollView 的 view 和 bar 事件
        if (this.goodsScrollView) {
            const view = this.goodsScrollView.node.getChildByName('view');
            const scrollbar = this.goodsScrollView.node.getChildByName('scrollBar');
            const bar = scrollbar?.getChildByName('bar');

            if (view) {
                view.on(Node.EventType.TOUCH_START, this.onViewTouchStart, this);
            }
            if (bar) {
                bar.on(Node.EventType.TOUCH_START, this.onBarTouchStart, this);
            }
        }

        // 绑定 Warehouse ScrollView 的 view 和 bar 事件
        if (this.warehouseScrollView) {
            const view = this.warehouseScrollView.node.getChildByName('view');
            const scrollbar = this.warehouseScrollView.node.getChildByName('scrollBar');
            const bar = scrollbar?.getChildByName('bar');

            if (view) {
                view.on(Node.EventType.TOUCH_START, this.onViewTouchStart, this);
            }
            if (bar) {
                bar.on(Node.EventType.TOUCH_START, this.onBarTouchStart, this);
            }
        }
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
        if (this.goodsScrollView && this.goodsScrollView.node.getChildByName('view')?.getComponent(UITransform)?.isHit(mousePosition)) {
            const deltaY = event.getScrollY(); // 获取滚轮垂直滚动量
            this.scrollContent(this.goodsScrollView, deltaY);
        }

        // 检查鼠标是否在 Warehouse ScrollView 的 view 区域内
        if (this.warehouseScrollView && this.warehouseScrollView.node.getChildByName('view')?.getComponent(UITransform)?.isHit(mousePosition)) {
            const deltaY = event.getScrollY(); // 获取滚轮垂直滚动量
            this.scrollContent(this.warehouseScrollView, deltaY);
        }
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
                const minY = 100; // 最小 Y 值
                const maxY = Math.max(viewTransform.height, contentTransform.height - 100); // 最大 Y 值
                const clampedY = Math.max(minY, Math.min(maxY, newY)); // 限制 Y 轴范围
                content.setPosition(content.position.x, clampedY, content.position.z);

                // 更新 bar 的位置
                this.updateBarPosition(scrollView, clampedY, minY, maxY);
            }
        }
    }

    /**
     * 更新 bar 的位置
     * @param scrollView 目标 ScrollView
     * @param contentY content 的 Y 坐标
     * @param minY content 的最小 Y 值
     * @param maxY content 的最大 Y 值
     */
    updateBarPosition(scrollView: ScrollView, contentY: number, minY: number, maxY: number) {
        const scrollbar = scrollView.node.getChildByName('scrollBar');
        const bar = scrollbar?.getChildByName('bar');

        if (scrollbar && bar) {
            const scrollbarTransform = scrollbar.getComponent(UITransform);
            const barTransform = bar.getComponent(UITransform);

            if (scrollbarTransform && barTransform) {
                const scrollRatio = (contentY - minY) / (maxY - minY); // 计算滚动比例
                const scrollbarHeight = scrollbarTransform.height;
                const barHeight = barTransform.height;

                // 计算 bar 的新位置
                const minBarY = - scrollbarHeight / 2; // bar 的最小 Y 值
                const maxBarY = scrollbarHeight / 2 - barHeight; // bar 的最大 Y 值
                const newY = minBarY + (maxBarY - minBarY) * (1 - scrollRatio); // 映射到 [minBarY, maxBarY] 区间

                // 更新 bar 的位置
                bar.setPosition(bar.position.x, newY, bar.position.z);
            }
        }
    }

    /**
     * view 触摸开始事件
     * @param event 触摸事件
     */
    onViewTouchStart(event: EventTouch) {
        const mousePosition = event.getLocation(); // 获取触摸点的位置
        const viewNode = this.goodsScrollView.node.getChildByName('view'); // 获取 view 节点

        // 检查触摸点是否在 view 节点的范围内
        if (viewNode?.getComponent(UITransform)?.isHit(mousePosition)) {
            const scrollView = viewNode.parent?.getComponent(ScrollView);

            if (scrollView) {
                this.currentScrollView = scrollView;
                this.isDragging = true; // 开始拖动
                this.lastMousePosition = mousePosition; // 记录初始位置
            }
        }
    }

    /**
     * bar 触摸开始事件
     * @param event 触摸事件
     */
    onBarTouchStart(event: EventTouch) {
        const mousePosition = event.getLocation(); // 获取触摸点的位置
        const scrollBarNode = this.goodsScrollView.node.getChildByName('scrollBar'); // 获取 scrollBar 节点
        const barNode = scrollBarNode?.getChildByName('bar'); // 获取 bar 节点

        // 检查触摸点是否在 bar 节点的范围内
        if (barNode?.getComponent(UITransform)?.isHit(mousePosition)) {
            const scrollView = scrollBarNode.parent?.getComponent(ScrollView);

            if (scrollView) {
                this.currentScrollView = scrollView;
                this.currentScrollbar = scrollBarNode;
                this.currentBar = barNode;
                this.isBarDragging = true; // 开始拖动 bar
            }
        }
    }

    /**
     * 鼠标移动事件
     * @param event 鼠标事件
     */
    onMouseMove(event: EventMouse) {
        if (this.isDragging && this.currentScrollView) {
            const mousePosition = event.getLocation();
            const deltaY = mousePosition.y - this.lastMousePosition.y; // 计算垂直偏移量

            // 滚动当前 ScrollView
            this.scrollContent(this.currentScrollView, -deltaY);

            this.lastMousePosition = mousePosition; // 更新上一次鼠标位置
        }

        if (this.isBarDragging && this.currentScrollView && this.currentScrollbar && this.currentBar) {
            const mousePosition = event.getLocation();
            const scrollbarTransform = this.currentScrollbar.getComponent(UITransform);
            const barTransform = this.currentBar.getComponent(UITransform);

            if (scrollbarTransform && barTransform) {
                // 获取 scrollbar 的世界坐标
                const scrollbarWorldPos = this.currentScrollbar.worldPosition;

                // 计算 bar 的中心位置
                const barHeight = barTransform.height;
                const scrollbarHeight = scrollbarTransform.height;

                // 限制 bar 的移动范围
                const minBarY = -scrollbarHeight / 2; // bar 的最小 Y 值
                const maxBarY = scrollbarHeight / 2 - barHeight; // bar 的最大 Y 值

                // 计算 bar 的新 Y 值（以中心为基准）
                const newY = Math.max(minBarY, Math.min(maxBarY, mousePosition.y - scrollbarWorldPos.y - barHeight / 2));

                // 只有当 bar 的位置发生变化时才更新
                if (this.currentBar.position.y !== newY) {
                    // 更新 bar 的位置
                    this.currentBar.setPosition(this.currentBar.position.x, newY, this.currentBar.position.z);

                    // 根据 bar 的位置计算内容滚动比例
                    const scrollRatio = (newY - minBarY) / (maxBarY - minBarY);
                    this.scrollContentByBar(this.currentScrollView, 1 - scrollRatio); // 1 - scrollRatio 因为 Y 值越小，bar 越靠下
                }
            }
        }
    }

    /**
     * 鼠标松开事件
     */
    onMouseUp() {
        this.isDragging = false; // 停止拖动
        this.isBarDragging = false; // 停止拖动 bar
        this.currentScrollView = null;
        this.currentScrollbar = null;
        this.currentBar = null;
    }

    /**
     * 根据 bar 的位置滚动内容
     * @param scrollView 目标 ScrollView
     * @param scrollRatio 滚动比例 (0-1)
     */
    scrollContentByBar(scrollView: ScrollView, scrollRatio: number) {
        const content = scrollView.content;
        if (content) {
            const contentTransform = content.getComponent(UITransform);
            const viewTransform = scrollView.node.getComponent(UITransform);

            if (contentTransform && viewTransform) {
                const minY = 100; // content 的最小 Y 值
                const maxY = Math.max(viewTransform.height, contentTransform.height - 100); // content 的最大 Y 值
                const newY = minY + (maxY - minY) * scrollRatio;

                // 更新 content 的位置
                content.setPosition(content.position.x, newY, content.position.z);
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