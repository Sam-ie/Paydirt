import { _decorator, Component, Node, Button, Color, Sprite, UITransform, director } from 'cc';
import EventConstants from '../Startup/EventConstants'; // 导入全局事件名称
const { ccclass, property } = _decorator;

@ccclass('MarketFunction')
export class MarketFunction extends Component {
    @property(Node) // 绑定 Buttons 节点
    buttons: Node = null;

    @property(Node) // 绑定 Goods ScrollView 组件
    goodsScrollView: Node = null;

    private newsButton: Button | null = null; // News 按钮
    private jumpTimeButton: Button | null = null; // JumpTime 按钮
    private upgradeButton: Button | null = null; // Upgrade 按钮
    private returnButton: Button | null = null; // Return 按钮

    private grayMask: Node | null = null; // 灰色蒙版
    private yellowBackground: Node | null = null; // 黄色背景

    start() {
        // 获取按钮组件
        this.newsButton = this.buttons.getChildByName('News')?.getComponent(Button);
        this.jumpTimeButton = this.buttons.getChildByName('JumpTime')?.getComponent(Button);
        this.upgradeButton = this.buttons.getChildByName('Upgrade')?.getComponent(Button);
        this.returnButton = this.buttons.getChildByName('Return')?.getComponent(Button);

        if (!this.newsButton || !this.jumpTimeButton || !this.upgradeButton || !this.returnButton) {
            console.error('按钮未找到');
            return;
        }

        // 绑定按钮事件
        this.bindButtonEvents(this.newsButton, this.onNewsTouchEnd.bind(this));
        this.bindButtonEvents(this.jumpTimeButton, this.onJumpTimeTouchEnd.bind(this));
        this.bindButtonEvents(this.upgradeButton, this.onUpgradeTouchEnd.bind(this));
        this.bindButtonEvents(this.returnButton, this.onReturnTouchEnd.bind(this));
    }

    /**
     * 绑定按钮的触摸事件
     * @param button 按钮组件
     * @param onTouchEnd 触摸结束的回调函数
     */
    bindButtonEvents(button: Button, onTouchEnd: (event: EventTouch) => void) {
        if (!button) return;

        button.node.on(Node.EventType.TOUCH_START, () => {
            // 触摸开始，无需日志
        });

        button.node.on(Node.EventType.TOUCH_END, onTouchEnd);

        button.node.on(Node.EventType.TOUCH_CANCEL, () => {
            // 触摸取消，无需日志
        });
    }

    /**
     * 创建灰色蒙版
     */
    createGrayMask() {
        // 创建灰色蒙版节点
        this.grayMask = new Node('GrayMask');
        const maskSprite = this.grayMask.addComponent(Sprite);
        const maskTransform = this.grayMask.addComponent(UITransform);

        // 设置蒙版颜色为灰色
        maskSprite.color = new Color(128, 128, 128, 200); // 半透明灰色

        // 设置蒙版大小为覆盖整个 Canvas
        const canvas = this.node.parent;
        if (canvas) {
            const canvasTransform = canvas.getComponent(UITransform);
            if (canvasTransform) {
                maskTransform.width = canvasTransform.width;
                maskTransform.height = canvasTransform.height;
            }
        }

        // 将蒙版添加到 Canvas
        this.node.parent?.addChild(this.grayMask);
    }

    /**
     * 创建黄色背景
     */
    createYellowBackground() {
        // 创建黄色背景节点
        this.yellowBackground = new Node('YellowBackground');
        const backgroundSprite = this.yellowBackground.addComponent(Sprite);
        const backgroundTransform = this.yellowBackground.addComponent(UITransform);

        // 设置背景颜色为黄色
        backgroundSprite.color = Color.YELLOW;

        // 设置背景大小为 300x260
        backgroundTransform.width = 300;
        backgroundTransform.height = 260;

        // 将背景添加到蒙版之上
        if (this.grayMask) {
            this.grayMask.addChild(this.yellowBackground);
        }
    }

    /**
     * 移除灰色蒙版和黄色背景
     */
    removeMaskAndBackground() {
        if (this.grayMask) {
            this.grayMask.destroy();
            this.grayMask = null;
        }
        if (this.yellowBackground) {
            this.yellowBackground.destroy();
            this.yellowBackground = null;
        }
    }

    /**
     * News 按钮触摸结束事件
     */
    onNewsTouchEnd(event: EventTouch) {
        this.createGrayMask();
        this.createYellowBackground();
    }

    /**
     * JumpTime 按钮触摸结束事件
     */
    onJumpTimeTouchEnd(event: EventTouch) {
        // 触发时间跳跃事件
        director.emit(EventConstants.TIME_JUMP_EVENT);
    }

    /**
     * Upgrade 按钮触摸结束事件
     */
    onUpgradeTouchEnd(event: EventTouch) {
        // 获取 ScrollView 节点下的 GenarateItems 脚本
        const genarateItems = this.goodsScrollView.getComponent('GenarateItems');
        if (genarateItems && genarateItems.addLevel) {
            // 调用 addLevel 方法
            genarateItems.addLevel();
        } else {
            console.error("GenarateItems 脚本或 addLevel 方法未找到");
        }
    }

    /**
     * Return 按钮触摸结束事件
     */
    onReturnTouchEnd(event: EventTouch) {
        // 返回 Select 场景
        director.loadScene('Select');
    }
}