// Box width
var bw = 1890;
// Box height
var bh = 920;
// Padding
var p = 0;

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
    context.stroke();
}

function drawCrates() {} //Draws the crates that are already present

function animateMove() {} //Draws the animation of a crate moving

drawBoard();