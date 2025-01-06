import { _decorator, Component, Label, HorizontalTextAlignment, VerticalTextAlignment, Color } from 'cc';
const { ccclass, property } = _decorator;

@ccclass('IntroduceText')
export class IntroduceText extends Component {

    @property(Label) // 绑定 Label 组件
    label: Label = null;

    start() {
        this.updateText();
    }

    /**
     * 更新文本内容
     */
    updateText() {
        // 从本地存储中读取全局变量 year、month 和 total_property
        let year = this.getGlobalVariable('year', 1); // 如果本地没有，默认值为 1
        let month = this.getGlobalVariable('month', 1); // 如果本地没有，默认值为 1
        let total_property = this.getGlobalVariable('total_property', 0); // 如果本地没有，默认值为 0

        // 格式化总资产，保留两位小数，并在小数点前每三位添加逗号
        const formattedTotalProperty = this.formatNumber(total_property);

        // 设置文本内容
        this.label.string = `第 ${year} 年第 ${month} 月\n您的总资产估值为 ${formattedTotalProperty} 元\n其中商品估值 ${formattedTotalProperty} 元\n拍卖品估值 ${formattedTotalProperty} 元\n彩票估值 ${formattedTotalProperty} 元\n资产估值 ${formattedTotalProperty} 元\n\n您想做什么：`;

        // 设置文本居中对齐
        this.label.horizontalAlign = HorizontalTextAlignment.CENTER;
        this.label.verticalAlign = VerticalTextAlignment.CENTER;
        
        // 设置字体颜色为 #000000（黑色）
        this.label.color = new Color(0, 0, 0, 255);
    }

    /**
     * 更新时间
     * @param mode 模式：0 - 重置为第1年第1月；1 - 月份+1
     */
    changeTime(mode: number) {
        let year = this.getGlobalVariable('year', 1);
        let month = this.getGlobalVariable('month', 1);

        if (mode === 0) {
            // 重置为第1年第1月
            year = 1;
            month = 1;
        } else if (mode === 1) {
            // 月份+1
            month += 1;
            if (month > 12) {
                month = 1;
                year += 1;
            }
        }

        // 保存到本地存储
        localStorage.setItem('year', JSON.stringify(year));
        localStorage.setItem('month', JSON.stringify(month));

        console.log("当前时间:", `第 ${year} 年第 ${month} 月`);

        // 更新文本内容
        this.updateText();
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

    /**
     * 从本地存储中读取全局变量，如果不存在则设置默认值
     * @param key 变量名
     * @param defaultValue 默认值
     * @returns 读取的值或默认值
     */
    private getGlobalVariable(key: string, defaultValue: number): number {
        const savedValue = localStorage.getItem(key);
        if (savedValue) {
            return JSON.parse(savedValue);
        } else {
            localStorage.setItem(key, JSON.stringify(defaultValue));
            return defaultValue;
        }
    }
}