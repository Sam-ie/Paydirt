import { _decorator, Component, Node } from 'cc';
const { ccclass, property } = _decorator;

@ccclass('AssessProperty')
export class AssessProperty extends Component {
    start() {

    }
    
    assess() {
        // 在这里实现属性计算的逻辑
        console.log("调用 AssessProperty 脚本");
    }

    update(deltaTime: number) {
        
    }
}


