import { _decorator, Component, Node } from 'cc';
const { ccclass, property } = _decorator;

@ccclass('BackgroundControl')
export class BackgroundControl extends Component {
    start() {

    }

    update(deltaTime: number) {
        //移动
        //遍历子物体
        for (let bgNode of this.node.children) {
            bgNode.setPosition(bgNode.position.x - 50 * deltaTime, bgNode.position.y);
            if (bgNode.position.x < -1064)
                bgNode.setPosition(bgNode.position.x + 2 * 1064, bgNode.position.y);
        }
    }
}


