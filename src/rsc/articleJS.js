// 在页面加载完成之后，将所有音频连接加上onclick事件
// onclick的处理函数为 playAudio
// 实现点击音频连接，直接在当前网页播放，而不进行转跳


// 当页面加载完成之后，指向audioLinkInit()
window.addEventListener("load", audioLinkInit);


function playAudio(event) {
    // 阻止默认行为，即点击链接时不跳转到链接的 URL
    event.preventDefault();
    // 查找audioPlayer
    var audioPlayer = document.getElementById('audioPlayer');
    // 判断audio是否存在
    if (audioPlayer !== undefined) {
        // 获取音频地址
        var audioSource = event.currentTarget.getAttribute('href');
        console.log(audioSource);
        audioPlayer.src = audioSource;
        // 播放音频
        audioPlayer.play();
    } else {
        console.log("audio element 'audioPlayer' is undefined");
    }
}
// 为所有音频 <a> 标签加上 onclick事件
function audioLinkInit() {
    console.log("begin");
    // 找到所有a标签
    var audioElements = document.getElementsByTagName("a");
    // 为所有资源类型为 MP3 的文件加上onclick事件
    for (var audioElement of audioElements) {
        if (audioElement.href.match(".mp3")) {
            console.log(audioElement.href);
            audioElement.onclick = playAudio;
        }
    }
}

// 中英切换开关
function languageSwitch() {
    // 获取按钮现在的文本
    var buttonElements = document.getElementsByClassName("language-button");
    var language = "Enlish";
    var isDisplay = "none";
    // 对按钮文本进行切换
    if (buttonElements[0].innerHTML.match(language)) {
        language = "Chinese"
        buttonElements[0].innerHTML = language;
        isDisplay = "inline";
    } else {
        buttonElements[0].innerHTML = "Enlish";
    }

    // 显示或者隐藏
    var chineseElements = document.getElementsByTagName("chn");
    for (var chineseElement of chineseElements) {
        chineseElement.style.setProperty('display', isDisplay, 'important');
    }
}

