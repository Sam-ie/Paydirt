// IntroduceText.ts
import { _decorator, Component, Label, HorizontalTextAlignment, VerticalTextAlignment, Color } from 'cc';
import { Paydirt } from './Paydirt'; // 导入 Paydirt
const { ccclass, property } = _decorator;

@ccclass('IntroduceText')
export class IntroduceText extends Component {

    // 单例实例
    private static instance: IntroduceText;

    @property(Label) // 绑定 Label 组件
    private label: Label = null;

    private paydirt: Paydirt;

    onLoad() {
        // 设置单例实例
        IntroduceText.instance = this;

        // 获取 Paydirt 实例
        this.paydirt = Paydirt.getInstance();

        // 初始化文本
        this.updateText();
    }

    // 获取单例实例
    public static getInstance(): IntroduceText {
        return IntroduceText.instance;
    }

    /**
     * 更新文本内容
     */
    public updateText() {
        if (!this.label) {
            return;
        }

        // 获取年、月和总资产
        const year = this.paydirt.Year;
        const month = this.paydirt.Month;
        const totalProperty = this.paydirt.TotalProperty;

        // 获取 Market 钱数、Auction 钱数、Lottery 钱数、Investment 钱数和活期余额
        const marketMoney = this.paydirt.MarketMoney;
        const auctionMoney = this.paydirt.AuctionMoney;
        const lotteryMoney = this.paydirt.LotteryMoney;
        const investmentMoney = this.paydirt.InvestmentMoney;
        const currentBalance = this.paydirt.CurrentBalance;

        // 格式化数值
        const formattedTotalProperty = this.formatNumber(totalProperty);
        const formattedMarketMoney = this.formatNumber(marketMoney);
        const formattedAuctionMoney = this.formatNumber(auctionMoney);
        const formattedLotteryMoney = this.formatNumber(lotteryMoney);
        const formattedInvestmentMoney = this.formatNumber(investmentMoney);
        const formattedCurrentBalance = this.formatNumber(currentBalance);

        // 设置文本内容
        this.label.string =
            `第 ${year} 年第 ${month} 月\n` +
            `您的总资产估值为 ${formattedTotalProperty} 元\n` +
            `商品估值：${formattedMarketMoney} 元\n` +
            `拍卖品估值：${formattedAuctionMoney} 元\n` +
            `彩票估值：${formattedLotteryMoney} 元\n` +
            `资产估值：${formattedInvestmentMoney} 元\n` +
            `活期余额：${formattedCurrentBalance} 元\n\n` +
            `您想做什么：`;

        // 设置文本居中对齐
        this.label.horizontalAlign = HorizontalTextAlignment.CENTER;
        this.label.verticalAlign = VerticalTextAlignment.CENTER;

        // 设置字体颜色为 #000000（黑色）
        this.label.color = new Color(0, 0, 0, 255);
    }

    /**
     * 格式化数字，保留两位小数，并在小数点前每三位添加逗号
     * @param num 要格式化的数字
     * @returns 格式化后的字符串
     */
    private formatNumber(num: number): string {
        return num.toLocaleString('en-US', {
            minimumFractionDigits: 2, // 最少保留两位小数
            maximumFractionDigits: 2, // 最多保留两位小数
        });
    }
}