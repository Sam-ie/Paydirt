// Paydirt.ts
import { director } from 'cc';
import { MarketController } from '../Market/MarketController'; // 导入 MarketController
import { IntroduceText } from './IntroduceText'; // 导入 IntroduceText

export class Paydirt {
    // 单例模式
    private static instance: Paydirt;

    // 年、月、Market 钱数、Auction 钱数、Lottery 钱数、Investment 钱数、活期余额
    private year: number = 1;
    private month: number = 1;
    private marketMoney: number = 0;
    private auctionMoney: number = 0;
    private lotteryMoney: number = 0;
    private investmentMoney: number = 0;
    private currentBalance: number = 0;

    // IntroduceText 实例
    private introduceText: IntroduceText | null = null;

    // 初次场景加载时更新用
    // public onLoad: boolean[] = [true, true, true, true, true];

    private constructor() {
        // 从本地存储加载数据
        this.loadFromLocalStorage();

        // 监听时间跳跃事件
        director.on('time-jump-event', this.onTimeJump, this);
    }

    // 获取单例实例
    public static getInstance(): Paydirt {
        if (!Paydirt.instance) {
            Paydirt.instance = new Paydirt();
        }
        return Paydirt.instance;
    }

    /**
     * 从本地存储加载数据
     */
    private loadFromLocalStorage() {
        this.year = this.getNumberFromLocalStorage('year', 1);
        this.month = this.getNumberFromLocalStorage('month', 1);
        this.marketMoney = this.getNumberFromLocalStorage('marketMoney', 0);
        this.auctionMoney = this.getNumberFromLocalStorage('auctionMoney', 0);
        this.lotteryMoney = this.getNumberFromLocalStorage('lotteryMoney', 0);
        this.investmentMoney = this.getNumberFromLocalStorage('investmentMoney', 0);
        this.currentBalance = this.getNumberFromLocalStorage('currentBalance', 0);
    }

    /**
     * 保存数据到本地存储
     */
    private saveToLocalStorage() {
        localStorage.setItem('year', JSON.stringify(this.year));
        localStorage.setItem('month', JSON.stringify(this.month));
        localStorage.setItem('marketMoney', JSON.stringify(this.marketMoney));
        localStorage.setItem('auctionMoney', JSON.stringify(this.auctionMoney));
        localStorage.setItem('lotteryMoney', JSON.stringify(this.lotteryMoney));
        localStorage.setItem('investmentMoney', JSON.stringify(this.investmentMoney));
        localStorage.setItem('currentBalance', JSON.stringify(this.currentBalance));
    }

    /**
     * 从本地存储读取数字，如果不存在则设置默认值
     * @param key 键名
     * @param defaultValue 默认值
     * @returns 读取的值或默认值
     */
    private getNumberFromLocalStorage(key: string, defaultValue: number): number {
        const savedValue = localStorage.getItem(key);
        if (savedValue) {
            return JSON.parse(savedValue);
        } else {
            localStorage.setItem(key, JSON.stringify(defaultValue));
            return defaultValue;
        }
    }

    private onTimeJump() {
        // 调用自身的 changeTime 方法
        this.changeTime(1);

        // 通知 IntroduceText 更新文本
        const introduceText = IntroduceText.getInstance();
        if (introduceText) {
            // 调用 IntroduceText 的 updateText 方法
            introduceText.updateText();
        }

        // 获取 MarketController 实例
        const marketController = MarketController.getInstance();
        if (!marketController) {
            console.error('MarketController 未初始化');
            return;
        }

        // 调用 MarketController 的 timePass 函数
        marketController.timePass();
    }

    /**
     * 更新时间
     * @param mode 模式：0 - 重置为第1年第1月；1 - 月份+1
     */
    public changeTime(mode: number) {
        if (mode === 0) {
            // 重置为第1年第1月
            this.year = 1;
            this.month = 1;
        } else if (mode === 1) {
            // 月份+1
            this.month += 1;
            if (this.month > 12) {
                this.month = 1;
                this.year += 1;
            }
        }

        // 保存到本地存储
        this.saveToLocalStorage();

        console.log("当前时间:", `第 ${this.year} 年第 ${this.month} 月`);
    }

    // ==================== 成员变量的 get-set 接口 ====================

    /**
     * 获取总资产
     * @returns 总资产
     */
    public get TotalProperty(): number {
        return this.marketMoney + this.auctionMoney + this.lotteryMoney + this.investmentMoney + this.currentBalance;
    }

    /**
     * 获取年
     */
    public get Year(): number {
        return this.year;
    }

    /**
     * 设置年
     */
    public set Year(value: number) {
        this.year = value;
        this.saveToLocalStorage();
    }

    /**
     * 获取月
     */
    public get Month(): number {
        return this.month;
    }

    /**
     * 设置月
     */
    public set Month(value: number) {
        this.month = value;
        this.saveToLocalStorage();
    }

    /**
     * 获取 Market 钱数
     */
    public get MarketMoney(): number {
        return this.marketMoney;
    }

    /**
     * 设置 Market 钱数
     */
    public set MarketMoney(value: number) {
        this.marketMoney = value;
        this.saveToLocalStorage();
    }

    /**
     * 获取 Auction 钱数
     */
    public get AuctionMoney(): number {
        return this.auctionMoney;
    }

    /**
     * 设置 Auction 钱数
     */
    public set AuctionMoney(value: number) {
        this.auctionMoney = value;
        this.saveToLocalStorage();
    }

    /**
     * 获取 Lottery 钱数
     */
    public get LotteryMoney(): number {
        return this.lotteryMoney;
    }

    /**
     * 设置 Lottery 钱数
     */
    public set LotteryMoney(value: number) {
        this.lotteryMoney = value;
        this.saveToLocalStorage();
    }

    /**
     * 获取 Investment 钱数
     */
    public get InvestmentMoney(): number {
        return this.investmentMoney;
    }

    /**
     * 设置 Investment 钱数
     */
    public set InvestmentMoney(value: number) {
        this.investmentMoney = value;
        this.saveToLocalStorage();
    }

    /**
     * 获取活期余额
     */
    public get CurrentBalance(): number {
        return this.currentBalance;
    }

    /**
     * 设置活期余额
     */
    public set CurrentBalance(value: number) {
        this.currentBalance = value;
        this.saveToLocalStorage();
    }
}