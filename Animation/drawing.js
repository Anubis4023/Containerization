// Box width
var bw = 1890;
// Box height
var bh = 920;
// Padding
var p = 0;

//Crate width
var cw = 154;
//Crate height
var ch = 112;

var canvas = document.getElementById("myCanvas");
var context = canvas.getContext("2d");

function drawBoard(){ //Draws the 8x12 grid
    for (var x = 0; x <= bw; x += bw/12) {
        context.moveTo(0.5 + x + p, p);
        context.lineTo(0.5 + x + p, bh + p);
    }

    for (var x = 0; x <= bh; x += bh/8) {
        context.moveTo(p, 0.5 + x + p);
        context.lineTo(bw + p, 0.5 + x + p);
    }
    context.strokeStyle = "black";
    context.lineWidth = 4;
    context.stroke();
}

function generateRandomColor(){
    let maxVal = 0xFFFFFF; // 16777215
    let randomNumber = Math.random() * maxVal; 
    randomNumber = Math.floor(randomNumber);
    randomNumber = randomNumber.toString(16);
    let randColor = randomNumber.padStart(6, 0);   
    return `#${randColor.toUpperCase()}`
}

function drawCrates(positions) { //Draws the crates that are already present
    for (let i = 0; i < positions.length; ++i) {
        context.fillStyle = generateRandomColor();
        context.fillRect(2 + 157.5*positions[i][0], 2 + 115*positions[i][1], cw, ch);
    }
}

function animateMove() {} //Draws the animation of a crate moving

//drawBoard();
let positions = [[0,0], [0,3]];
//drawCrates(positions);

//drawCrates([0,0]);


//context.fillStyle = 'red';
//context.fillRect(2, 2, cw, ch);
/*for (let i = 0; i < 8; ++i) {
    for (let j = 0; j < 12; ++j) {
        context.fillStyle = generateRandomColor();
        context.fillRect(2 + 157.5*j, 2 + 115*i, cw, ch);
    }
} */
//context.fillStyle = 'blue';
//context.fillRect(2+157.5, 2+115, cw, ch);