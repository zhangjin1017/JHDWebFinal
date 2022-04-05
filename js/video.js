
//�����Ƶ����
var myVideo = document.getElementById('myVideo');

/*������ͣ*/
function playPause(btn) {
    if (myVideo.paused) {
        myVideo.play();
        btn.value = '��ͣ';
    } else {
        myVideo.pause();
        btn.value = '����';
    }
}

/*���Ž����¼��ص�*/
myVideo.onended = function () {
    alert('���Ž���');
    document.getElementById('playBtn').value = '����';
}

/*ǰ������*/
function forwardBack(i) {
    myVideo.currentTime += i;
}

/*���ٲ���*/
function toFast() {
    myVideo.playbackRate = 3;
}

/*���ٲ���*/
function toSlow() {
    myVideo.playbackRate = 1 / 3;
}

/*��������*/
function toNormal() {
    myVideo.playbackRate = 1;
}
