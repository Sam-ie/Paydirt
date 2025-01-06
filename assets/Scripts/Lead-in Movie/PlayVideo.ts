import { _decorator, Component, VideoPlayer, director } from 'cc';
const { ccclass, property } = _decorator;


@ccclass('PlayVideo')
export class PlayVideo extends Component {

    @property(VideoPlayer) // 绑定 VideoPlayer 组件
    videoPlayer: VideoPlayer = null;

    // 局部变量，标记是否已经播放过视频
    private isLeadInVideoPlayed: boolean = false;

    start() {
        // 删除所有本地存储变量
        localStorage.clear();
        // 从本地存储中读取是否已经播放过视频
        const savedValue = localStorage.getItem('isLeadInVideoPlayed');
        if (savedValue) {
            this.isLeadInVideoPlayed = JSON.parse(savedValue);
        }

        if (this.isLeadInVideoPlayed) {
            // 如果已经播放过视频，直接跳转到 Select 场景
            this.gotoSelectScene();
        } else {
            // 第一次进入场景，播放视频
            if (this.videoPlayer) {
                this.videoPlayer.node.on(VideoPlayer.EventType.COMPLETED, this.onVideoCompleted, this);
                this.videoPlayer.play();
            }
        }
    }

    onVideoCompleted() {
        // 视频播放完成后，设置全局变量并保存到本地存储
        this.isLeadInVideoPlayed = true;
        localStorage.setItem('isLeadInVideoPlayed', JSON.stringify(this.isLeadInVideoPlayed));

        // 跳转到 Select 场景
        this.gotoSelectScene();
    }

    gotoSelectScene() {
        director.loadScene("Select", (err) => {
            if (err) {
                console.error("跳转场景失败:", err);
            } else {
                console.log("成功跳转到 Select 场景");
            }
        });
    }
}