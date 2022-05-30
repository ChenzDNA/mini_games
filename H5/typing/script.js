// 生成‘石头’的间隔
var interval = 100;
// 计数，如果和间隔一样就生成石头
var time = interval;
// 下落速度
var speed = 3;
// 判断游戏结束
var gameOver = false;
// 生成的字符从这里随机取
var str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
// 作为setInterval的返回值
var down;
// 分数
var score = 0;
// 开始倒计时
function countdown() {
    score = 0;
    document.getElementById('scorenum').innerHTML = score;
    let hint = document.getElementById('hint');
    var countTime = 3;
    let count = setInterval(() => {
        hint.innerHTML = countTime;
        if (!countTime) {
            clearInterval(count);
            hint.innerHTML = '游戏开始！';
            document.getElementById('input').focus();
            down = setInterval(fall, 20);
        }
        countTime -= 1;
    }, 1000);
}
countdown();

// 下降
function fall() {
    let stones = document.getElementsByClassName('stone');
    // 如果次数达到设定的值，生成一个新的石头
    if (time == interval) {
        let newStone = document.createElement('div');
        newStone.setAttribute('class', 'stone');
        // 随机字符
        newStone.innerHTML = str[Math.round(Math.random() * 25)];
        // 随机位置
        newStone.style.left = `${Math.round(Math.random() * 80) + 10}%`
        let container = document.getElementById('container');
        // 把生成的石头添加到容器里
        container.appendChild(newStone);
        time = 0;
    }
    // 遍历每一个石头，修改其 css bottom 属性，实现下落
    for (let i = 0; i < stones.length; i += 1) {
        // 如果有‘stop’属性则跳过这个石头
        if (stones[i].hasAttribute('stop'))
            continue;
        // 计算下落的距离，赋值给style.bottom
        let distance = parseInt(getComputedStyle(stones[i]).bottom) - speed;
        stones[i].style.bottom = `${distance}px`;
        // 距离小于 150px 表示接触到地板，游戏结束
        if (distance < 150) {
            document.getElementById('hint').innerHTML = '游戏结束！'
            gameOver = true;
            clearInterval(down);
        }
    }
    time += 1;
}
// 按下按键触发的事件
function keydown() {
    // 晚1ms清空input里的字符，不然有可能清空失败
    setTimeout(() => {
        document.getElementById('input').value = '';
    }, 1);
    // 如果游戏结束，停止触发
    if (gameOver)
        return;
    // 遍历所有的石头，如果和键盘输入的值相同则移除最前面的石头
    let stones = document.getElementsByClassName('stone');
    let len = stones.length;
    for (let i = 0; i < len; i += 1) {
        // 判断石头的值是否和键盘输入的值相同
        if (arguments.callee.caller.arguments[0].key.toUpperCase() == stones[i].textContent) {
            let die = stones[i];
            die.innerHTML = '';
            // 设置过渡动画，0.3秒后移除
            die.setAttribute('stop', '');
            die.style.transition = '0.3s';
            die.style.transform = 'scale(0,0)';
            setTimeout(() => {
                die.parentElement.removeChild(die);
                die = null;
            }, 300);
            // 更新分数
            score += 1;
            document.getElementById('scorenum').innerHTML = score;
            break;
        }
    }
}
// 按下 重新开始键 触发的事件
function gameStart() {
    // 如果游戏没结束则不能重新开始，防止下落抖动
    if (!gameOver)
        return;
    // 从输入框获取各项参数
    interval = document.getElementById('interval').value;
    time = interval;
    speed = document.getElementById('speed').value;
    // 清空容器里的石头
    let container = document.getElementById('container');
    while (container.children.length) {
        container.children[0].remove();
    }
    gameOver = false;
    countdown();
}