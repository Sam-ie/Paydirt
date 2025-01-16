import { _decorator, Component, Node, EventTouch, director } from 'cc';
import EventConstants from '../Startup/EventConstants'; // 导入全局事件名称
const { ccclass, property } = _decorator;

@ccclass('SelectSceneEvents')
export class SelectSceneEvents extends Component {

    @property(Node) // 绑定 Market 按钮节点
    marketButton: Node = null;

    @property(Node) // 绑定 Auction 按钮节点
    auctionButton: Node = null;

    @property(Node) // 绑定 Lottery 按钮节点
    lotteryButton: Node = null;

    @property(Node) // 绑定 Property 按钮节点
    investmentButton: Node = null;

    @property(Node) // 绑定 TimeJump 按钮节点
    timeJumpButton: Node = null;

    @property(Node) // 绑定 IntroduceText 脚本所在的节点
    introduceTextNode: Node = null;

    private isButtonPressed: boolean = false; // 标记按钮是否被按住

    start() {
        // 绑定按钮的触摸事件
        this.bindButtonEvents(this.marketButton, 'Market');
        this.bindButtonEvents(this.auctionButton, 'Auction');
        this.bindButtonEvents(this.lotteryButton, 'Lottery');
        this.bindButtonEvents(this.investmentButton, 'Investment');
        this.bindButtonEvents(this.timeJumpButton, 'TimeJump');
    }

    /**
     * 绑定按钮的触摸事件
     * @param button 按钮节点
     * @param buttonType 按钮类型（Market、Auction、Lottery、Investment、TimeJump）
     */
    bindButtonEvents(button: Node, buttonType: string) {
        if (!button) return;

        button.on(Node.EventType.TOUCH_START, () => this.onButtonTouchStart(), this);
        button.on(Node.EventType.TOUCH_END, () => this.onButtonTouchEnd(buttonType), this);
        button.on(Node.EventType.TOUCH_CANCEL, () => this.onButtonTouchCancel(), this);
    }

    // 按钮的触摸开始事件
    onButtonTouchStart() {
        this.isButtonPressed = true;
    }

    // 按钮的触摸结束事件
    onButtonTouchEnd(buttonType: string) {
        if (this.isButtonPressed) {
            this.isButtonPressed = false;

            switch (buttonType) {
                case 'Market':
                    director.loadScene('Market');
                    break;
                case 'Auction':
                    director.loadScene('Auction');
                    break;
                case 'Lottery':
                    director.loadScene('Lottery');
                    break;
                case 'Investment':
                    director.loadScene('Investment');
                    break;
                case 'TimeJump':
                    this.handleTimeJump();
                    break;
                default:
                    console.warn(`未知按钮类型: ${buttonType}`);
                    break;
            }
        }
    }

    // 按钮的触摸取消事件
    onButtonTouchCancel() {
        this.isButtonPressed = false;
    }

    /**
     * 处理时间跳跃逻辑
     */
    handleTimeJump() {

        // 触发时间跳跃事件
        director.emit(EventConstants.TIME_JUMP_EVENT);

        // 调用 IntroduceText 脚本的 changeTime 方法，传入 1 表示月份+1
        const introduceText = this.introduceTextNode.getComponent('IntroduceText');
        if (introduceText) {
            introduceText.changeTime(1);
        }
    }
}