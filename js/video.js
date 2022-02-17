
//获得视频对象
var myVideo = document.getElementById('myVideo');

/*播放暂停*/
function playPause(btn) {
    if (myVideo.paused) {
        myVideo.play();
        btn.value = '暂停';
    } else {
        myVideo.pause();
        btn.value = '播放';
    }
}

/*播放结束事件回调*/
myVideo.onended = function () {
    alert('播放结束');
    document.getElementById('playBtn').value = '播放';
}

/*前进后退*/
function forwardBack(i) {
    myVideo.currentTime += i;
}

/*快速播放*/
function toFast() {
    myVideo.playbackRate = 3;
}

/*慢速播放*/
function toSlow() {
    myVideo.playbackRate = 1 / 3;
}

/*正常倍速*/
function toNormal() {
    myVideo.playbackRate = 1;
}
