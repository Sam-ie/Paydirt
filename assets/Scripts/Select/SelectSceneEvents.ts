import { _decorator, Component, Node, EventTouch, director } from 'cc';
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
    propertyButton: Node = null;

    @property(Node) // 绑定 TimeJump 按钮节点
    timeJumpButton: Node = null;

    @property(Node) // 绑定 AssessProperty 脚本所在的节点
    assessPropertyNode: Node = null;

    @property(Node) // 绑定 IntroduceText 脚本所在的节点
    introduceTextNode: Node = null;

    private isButtonPressed: boolean = false; // 标记按钮是否被按住

    start() {
        // 清除本地存储
        // localStorage.clear();
        
        // 绑定 Market 按钮的触摸事件
        this.marketButton.on(Node.EventType.TOUCH_START, this.onMarketButtonTouchStart, this);
        this.marketButton.on(Node.EventType.TOUCH_END, this.onMarketButtonTouchEnd, this);
        this.marketButton.on(Node.EventType.TOUCH_CANCEL, this.onMarketButtonTouchCancel, this);

        // 绑定 Auction 按钮的触摸事件
        this.auctionButton.on(Node.EventType.TOUCH_START, this.onAuctionButtonTouchStart, this);
        this.auctionButton.on(Node.EventType.TOUCH_END, this.onAuctionButtonTouchEnd, this);
        this.auctionButton.on(Node.EventType.TOUCH_CANCEL, this.onAuctionButtonTouchCancel, this);

        // 绑定 Lottery 按钮的触摸事件
        this.lotteryButton.on(Node.EventType.TOUCH_START, this.onLotteryButtonTouchStart, this);
        this.lotteryButton.on(Node.EventType.TOUCH_END, this.onLotteryButtonTouchEnd, this);
        this.lotteryButton.on(Node.EventType.TOUCH_CANCEL, this.onLotteryButtonTouchCancel, this);

        // 绑定 Property 按钮的触摸事件
        this.propertyButton.on(Node.EventType.TOUCH_START, this.onPropertyButtonTouchStart, this);
        this.propertyButton.on(Node.EventType.TOUCH_END, this.onPropertyButtonTouchEnd, this);
        this.propertyButton.on(Node.EventType.TOUCH_CANCEL, this.onPropertyButtonTouchCancel, this);

        // 绑定 TimeJump 按钮的触摸事件
        this.timeJumpButton.on(Node.EventType.TOUCH_START, this.onTimeJumpButtonTouchStart, this);
        this.timeJumpButton.on(Node.EventType.TOUCH_END, this.onTimeJumpButtonTouchEnd, this);
        this.timeJumpButton.on(Node.EventType.TOUCH_CANCEL, this.onTimeJumpButtonTouchCancel, this);
    }
    
    // Market 按钮的触摸开始事件
    onMarketButtonTouchStart(event: EventTouch) {
        this.isButtonPressed = true;
    }

    // Market 按钮的触摸结束事件
    onMarketButtonTouchEnd(event: EventTouch) {
        if (this.isButtonPressed) {
            this.isButtonPressed = false;
            // 跳转到 Market 界面
            director.loadScene("Market");
        }
    }

    // Market 按钮的触摸取消事件
    onMarketButtonTouchCancel(event: EventTouch) {
        this.isButtonPressed = false;
    }

    // Auction 按钮的触摸开始事件
    onAuctionButtonTouchStart(event: EventTouch) {
        this.isButtonPressed = true;
    }

    // Auction 按钮的触摸结束事件
    onAuctionButtonTouchEnd(event: EventTouch) {
        if (this.isButtonPressed) {
            this.isButtonPressed = false;
            // 跳转到 Auction 界面
            director.loadScene("Auction");
        }
    }

    // Auction 按钮的触摸取消事件
    onAuctionButtonTouchCancel(event: EventTouch) {
        this.isButtonPressed = false;
    }

    // Lottery 按钮的触摸开始事件
    onLotteryButtonTouchStart(event: EventTouch) {
        this.isButtonPressed = true;
    }

    // Lottery 按钮的触摸结束事件
    onLotteryButtonTouchEnd(event: EventTouch) {
        if (this.isButtonPressed) {
            this.isButtonPressed = false;
            // 跳转到 Lottery 界面
            director.loadScene("Lottery");
        }
    }

    // Lottery 按钮的触摸取消事件
    onLotteryButtonTouchCancel(event: EventTouch) {
        this.isButtonPressed = false;
    }

    // Property 按钮的触摸开始事件
    onPropertyButtonTouchStart(event: EventTouch) {
        this.isButtonPressed = true;
    }

    // Property 按钮的触摸结束事件
    onPropertyButtonTouchEnd(event: EventTouch) {
        if (this.isButtonPressed) {
            this.isButtonPressed = false;
            // 跳转到 Property 界面
            director.loadScene("Property");
        }
    }

    // Property 按钮的触摸取消事件
    onPropertyButtonTouchCancel(event: EventTouch) {
        this.isButtonPressed = false;
    }

    // TimeJump 按钮的触摸开始事件
    onTimeJumpButtonTouchStart(event: EventTouch) {
        this.isButtonPressed = true;
    }

    // TimeJump 按钮的触摸结束事件
    onTimeJumpButtonTouchEnd(event: EventTouch) {
        if (this.isButtonPressed) {
            this.isButtonPressed = false;
            
            // 调用 IntroduceText 脚本的 changeTime 方法，传入 1 表示月份+1
            const introduceText = this.introduceTextNode.getComponent('IntroduceText');
            if (introduceText) {
                introduceText.changeTime(1);
            }

            // 调用 AssessProperty 脚本
            const assessProperty = this.assessPropertyNode.getComponent('AssessProperty');
            if (assessProperty) {
                assessProperty.assess();
            }

            // 调用 IntroduceText 脚本的 updateText 方法
            if (introduceText) {
                introduceText.updateText();
            }
        }
    }

    // TimeJump 按钮的触摸取消事件
    onTimeJumpButtonTouchCancel(event: EventTouch) {
        this.isButtonPressed = false;
    }
}