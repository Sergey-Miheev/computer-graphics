function DrawM(ctx, x, y) {
    var randomColor = 'rgb(' + Math.floor(Math.random()*255) + ',' + Math.floor(Math.random()*255)
    + ',' + Math.floor(Math.random()*255);

    ctx.beginPath();
    ctx.moveTo(x, y);
    // up
    ctx.lineTo(x,y-300);
    // right
    ctx.lineTo(x+30,y-300);
    //middle
    ctx.lineTo(x+130,y-150);
    // right
    ctx.lineTo(x+230,y-300);
    // right
    ctx.lineTo(x+260,y-300);
    // down
    ctx.lineTo(x+260,y);
    // left
    ctx.lineTo(x+230,y);
    // up
    ctx.lineTo(x+230,y-240);
    // middle
    ctx.lineTo(x+130,y-90);
    // left
    ctx.lineTo(x+30,y-240);
    // down
    ctx.lineTo(x+30,y);
    // left
    ctx.lineTo(x,y);

    ctx.fillStyle = randomColor;

    ctx.fill();
}

function DrawC(ctx, x, y) {
    var randomColor = 'rgb(' + Math.floor(Math.random()*255) + ',' + Math.floor(Math.random()*255)
    + ',' + Math.floor(Math.random()*255);

    ctx.beginPath();

    ctx.moveTo(x, y);

    ctx.bezierCurveTo(x-200, y, x-200, y+300, x, y+300);

    ctx.lineTo(x, y+270); 

    ctx.bezierCurveTo(x-150, y+300, x-150, y+30, x, y+30);

    ctx.lineTo(x, y);

    ctx.fillStyle = randomColor;

    ctx.fill();
}

function DrawA(ctx, x, y) {
    var randomColor = 'rgb(' + Math.floor(Math.random()*255) + ',' + Math.floor(Math.random()*255)
    + ',' + Math.floor(Math.random()*255);

    ctx.beginPath();

    ctx.moveTo(x, y);
    //up
    ctx.lineTo(x+80, y-300);
    //right
    ctx.lineTo(x+110, y-300);
    //down
    ctx.lineTo(x+190, y);
    //left
    ctx.lineTo(x+160, y);
    //up
    ctx.lineTo(x+95, y-230);
    //down
    ctx.lineTo(x+30, y);
    //left
    ctx.lineTo(x, y);

    ctx.fillStyle = randomColor;
    ctx.fill();

    ctx.beginPath();

    ctx.moveTo(x+72, y-150);
    //down
    ctx.lineTo(x+64, y-120);
    //right
    ctx.lineTo(x+126, y-120);
    //up
    ctx.lineTo(x+118, y-150);

    ctx.fillStyle = randomColor;

    ctx.fill();
}

function DrawInitials() {
    var canvas = document.getElementById("canvas");
    if (canvas.getContext) {

        var ctx = canvas.getContext("2d");
        
        // буква М
        DrawM(ctx, 300, 430);

        // буква С
        DrawC(ctx, 830, 130);

        // буква А
        DrawA(ctx, 930, 430);
    }
}