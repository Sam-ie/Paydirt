import { _decorator, Component, Node, director } from 'cc';
import EventConstants from '../Startup/EventConstants'; // 导入全局事件名称
const { ccclass } = _decorator;

@ccclass('AssessProperty')
export class AssessProperty extends Component {
    start() {
        // 监听时间跳跃事件
        director.on(EventConstants.TIME_JUMP_EVENT, this.assess, this);
    }

    assess() {
        // 在这里实现属性计算的逻辑
        console.log("调用 AssessProperty 脚本");
    }

    onDestroy() {
        // 移除事件监听
        director.off(EventConstants.TIME_JUMP_EVENT, this.assess, this);
    }
}