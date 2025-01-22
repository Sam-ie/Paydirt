// GameInitializer.ts
import { MarketController } from '../Market/MarketController';

export class GameInitializer {
    public static initialize() {
        // 创建 MarketController 实例
        const marketController = new MarketController();
        MarketController.setInstance(marketController);

        console.log('MarketController 单例实例已设置');
    }
}

// 在游戏启动时调用
GameInitializer.initialize();