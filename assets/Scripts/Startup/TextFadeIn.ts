import { _decorator, Component, RichText, Color, input, Input, EventTouch, director } from 'cc';
const { ccclass, property } = _decorator;

@ccclass('TextTypingEffect')
export class TextTypingEffect extends Component {

    @property(RichText) // 绑定第一个 RichText 组件（橙色粗体文本）
    richText: RichText = null;

    @property(RichText) // 绑定第二个 RichText 组件（白色文本）
    whiteRichText: RichText = null;

    private fullText: string[] = ["  市 场", "模 拟 器"]; // 两行文本
    private currentText: string = "";
    private currentLine: number = 0;
    private index: number = 0;
    private isTyping: boolean = true;
    private timer: number = 0;
    private typingSpeed: number = 0.22; // 每个字的显示间隔（秒）
    private isWaiting: boolean = false; // 是否在等待 2 秒
    private isWhiteTextShowing: boolean = false; // 是否正在显示白色文本

    start() {
        if (this.richText) {
            this.richText.string = ""; // 初始化第一个 RichText
        }
        if (this.whiteRichText) {
            this.whiteRichText.string = ""; // 初始化第二个 RichText
        }

        // 监听点击事件
        input.on(Input.EventType.TOUCH_START, this.onTouchStart, this);
    }

    onDestroy() {
        // 移除点击事件监听
        input.off(Input.EventType.TOUCH_START, this.onTouchStart, this);
    }

    onTouchStart(event: EventTouch) {
        if (!this.isTyping) {
            // 点击任意位置后开始游戏
            this.startGame();
        }
    }

    update(deltaTime: number) {
        if (this.isTyping && this.richText) {
            this.timer += deltaTime; // 累计时间

            // 达到显示间隔时，逐字显示
            if (this.timer >= this.typingSpeed) {
                this.timer = 0; // 重置计时器

                if (this.currentLine < this.fullText.length) {
                    if (this.index < this.fullText[this.currentLine].length) {
                        // 逐字显示当前行的文本，并设置为橙色粗体
                        this.currentText += `<color=#FFA500><b>${this.fullText[this.currentLine][this.index]}</b></color>`;
                        this.richText.string = this.currentText;
                        this.index++;
                    } else {
                        // 当前行显示完毕，换到下一行
                        this.currentText += "<br/>"; // 添加换行
                        this.currentLine++;
                        this.index = 0;
                    }
                } else {
                    // 所有行显示完毕，停止逐字显示
                    this.isTyping = false;
                    this.isWaiting = true; // 开始等待 2 秒
                    this.timer = 0; // 重置计时器
                }
            }
        }

        if (this.isWaiting) {
            this.timer += deltaTime; // 累计等待时间

            // 等待 2 秒后，开始显示白色文本
            if (this.timer >= 2) {
                this.isWaiting = false;
                this.isWhiteTextShowing = true;
                this.timer = 0; // 重置计时器
            }
        }

        if (this.isWhiteTextShowing && this.whiteRichText) {
            // 设置白色文本内容
            this.whiteRichText.string = "点击任意位置开始游戏";
        }
    }

    startGame() {
        // 跳转到 "Lead-in Movie" 场景
        director.loadScene("Lead-in Movie", (err) => {
            if (err) {
                console.error("跳转场景失败:", err);
            }
        });
    }
}