// 蛇类
function Snake() {
    // 分数
    this.score = 0;
    // 方向，设置为数字方便判断
    // 1 left  2 up  3 right  4 down
    this.direction = 3;
}
// 重写Snake原型对象
Snake.prototype = {
    // 构造函数
    constructor: Snake,
    // 改变方向
    changeDirection: function (direction) {
        // 不能反向动（方向设置为数字的便利）
        if ((direction - this.direction) % 2)
            this.direction = direction;
    },
    // 吃
    eat: function () {
        // 加分
        this.score += 1;
        // 添加一个蛇身（div元素），innerHTML是选中的元素内的文本内容，还有一种方法.appendChild()，后面会用到
        document.getElementById('content').innerHTML += '<div class="snake"></div>';
        // 把修改的分数反映到界面
        document.getElementById('score-span').innerHTML = this.score;
        // 由于修改了innerHTML，需要重新聚焦到输入框里才能获取到键盘输入
        document.getElementById('kb-event').focus();
    },
    // 返回蛇头的坐标Array
    position: function () {
        // 获取到第一个class为snake的元素（蛇头）
        let head = document.getElementsByClassName('snake')[0]
        return [head.style.left, head.style.top];
    },
    // 判断蛇有没有吃到自己
    isDead: function () {
        // 获取所有class为snake的元素
        let nodes = document.getElementsByClassName('snake');
        // 把蛇身坐标依次与蛇头坐标比较
        for (let i = 1; i < nodes.length; i++) {
            if (nodes[0].style.left == nodes[i].style.left && nodes[0].style.top == nodes[i].style.top) {
                return true;
            }
        }
        return false;
    },
    // 蛇移动（先移动蛇身，再判断方向，移动蛇头），参数wall表示墙是否存在
    move: function (wall) {
        let nodes = document.getElementsByClassName('snake');
        // 把每个蛇身的坐标赋值为前一个蛇身的坐标，实现移动
        for (let i = nodes.length - 1; i > 0; i--) {
            nodes[i].style.left = nodes[i - 1].style.left;
            nodes[i].style.top = nodes[i - 1].style.top;
        }
        // 获取蛇头的坐标
        let left = parseInt(nodes[0].style.left);
        let top = parseInt(nodes[0].style.top);
        // 判断蛇头的移动方向并移动蛇头
        switch (this.direction) {
            case 1:
                nodes[0].style.left = `${left -= 5}px`;
                break;
            case 3:
                nodes[0].style.left = `${left += 5}px`;
                break;
            case 2:
                nodes[0].style.top = `${top -= 5}px`;
                break;
            case 4:
                nodes[0].style.top = `${top += 5}px`;
                break;
        }
        // 判断出界
        if (left < 0 || left > 495 || top < 0 || top > 495) {
            // 如果墙存在则返回false，在后面判断游戏结束
            if (wall) {
                return false;
            }
            // 墙不存在则把蛇头移动到对面
            else {
                if (left < 0) {
                    nodes[0].style.left = '495px';
                }
                else if (left > 495) {
                    nodes[0].style.left = '0';
                }
                else if (top < 0) {
                    nodes[0].style.top = '495px';
                }
                else {
                    nodes[0].style.top = '0';
                }
            }
        }
        return true;
    }
}
// 食物类
function Food() {
    // 分数（好像没什么用）（实际也没用到）
    this.score = 1;
}
// 重写食物原型对象
Food.prototype = {
    // 构造函数为Food
    constructor: Food,
    // 返回食物的坐标Array
    position: function () {
        let food = document.getElementsByClassName('food')[0]
        return [food.style.left, food.style.top];
    },
    // 食物被吃
    eaten: function () {
        // 用remove方法移除元素
        document.getElementsByClassName('food')[0].remove();
        // 重新生成食物
        this.generate();
    },
    // 生成食物
    generate: function () {
        // 随机坐标，Math.round()四舍五入，Math.random()生成0~1的随机小数
        let left = Math.round(Math.random() * 99);
        let top = Math.round(Math.random() * 99);
        // 新建食物元素
        let foodElem = document.createElement('div');
        // 设置class为food，也可用foodElem.setAttribute('class','food')设置class属性为food（把class当属性看）（实际上class就是属性）
        foodElem.className = 'food';
        // 把坐标赋值给食物元素，``表示字符串拼接，`${变量名或表达式}xxxx`
        foodElem.style.top = `${top * 5}px`;
        foodElem.style.left = `${left * 5}px`;
        // 把生成的食物元素加到content里面。（因为要改变坐标所以用createElement和appendChild方法）
        document.getElementById('content').appendChild(foodElem);
    }
}
// 速度
let speed = 1;
// 新建一个食物实例
let food = new Food();
// 蛇实例
let snake = new Snake();
// 本来想做一个倒计时开始的后来忘记了
let count = 0;
// 从键盘输入中获取方向
function getDirection() {
    // 获取键盘事件按下的按键，因为是在html元素里写的onkeydown触发这个函数，所以要写这么长来获取事件对象
    // 如果用addEventListener（下面会用到）把监听键盘事件就只要用arguments[0].key就行
    // callee和caller自己百度
    let direction = arguments.callee.caller.arguments[0].key;
    // 清空输入框里的值
    document.getElementById('kb-event').value = '';
    // 改变方向
    switch (direction) {
        case 'w':
        case 'ArrowUp': snake.changeDirection(2); return;
        case 's':
        case 'ArrowDown': snake.changeDirection(4); return;
        case 'a':
        case 'ArrowLeft': snake.changeDirection(1); return;
        case 'd':
        case 'ArrowRight': snake.changeDirection(3); return;
    }
}
// 改变速度
function changeSpeed() {
    let speedIn = document.getElementById('speed').value;
    // 速度限制在1~299内
    if (speedIn > 0 && speedIn < 300)
        speed = speedIn;
    else
        document.getElementById('speed').value = 1;
    // 重新聚焦输入框
    document.getElementById('kb-event').focus();
}
// 给checkbox添加的事件，改变墙的样式
let check = false;
function checkBox() {
    check = !check;
    let content = document.getElementById('content');
    if (check) {
        content.style.borderColor = 'black';
    }
    else {
        content.style.borderColor = 'white';
    }
}
// addEventListener会给callback函数传一个事件对象作为参数（虽然这里没用到这个参数）
document.getElementById('wall').addEventListener('click', checkBox);

// 获取到下面的wasd按键，用来添加事件
let buttons = document.getElementById('direction-button').children;
// 方向代表的数字
let directionNums = [2, 1, 3, 4];
// 下标
let subNum = 0;
// 给按键设置点击触发的函数
for (let item of buttons) {
    // 因为按键里混入了<br/>元素所以要加一个判断
    if (item.tagName == 'BUTTON') {
        item.setAttribute('onclick', `snake.changeDirection(${directionNums[subNum]})`);
        subNum += 1;
    }
}

// 先生成食物
food.generate();
function run() {
    // 蛇头和食物坐标相等，则吃
    if (snake.position().join() == food.position().join()) {
        snake.eat();
        food.eaten();
    }

    // 判断蛇有没有死，死了就结束
    if (!(snake.move(check)) || snake.isDead()) {
        hintSpan = document.getElementById('hint-span');
        hintSpan.style.fontSize = '30px';
        hintSpan.innerHTML = '游戏结束';
        return;
    }
    // 用setTimeout来实现循环，setTimeout能动态改变循环时间（应用速度）
    // setInterval不能动态改变循环时间
    setTimeout(run, 300 / speed);
}
setTimeout(run, 300 / speed);
console.log(new Snake())