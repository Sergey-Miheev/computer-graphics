function DrawRoof(ctx, x, y) {
    ctx.beginPath();

    ctx.moveTo(x, y);
    // up
    ctx.lineTo(x+250,y-250);
    // right
    ctx.lineTo(x+500,y);
    // коричневый 
    ctx.fillStyle = 'rgb(205,154,123)';

    ctx.fill();

    ctx.beginPath();

    ctx.moveTo(x, y);
    // up
    ctx.lineTo(x+250,y-250);
    // right
    ctx.lineTo(x+500,y);

    ctx.lineTo(x,y);

    ctx.stroke();
    ctx.closePath();

    ctx.beginPath();

    ctx.moveTo(x+40,y-40);
    // right
    ctx.lineTo(x+460,y-40);

    ctx.stroke();
    ctx.closePath();

    ctx.beginPath();

    ctx.moveTo(x+80,y-80);
    // right
    ctx.lineTo(x+420,y-80);

    ctx.stroke();
    ctx.closePath();

    ctx.beginPath();

    ctx.moveTo(x+120,y-120);
    // right
    ctx.lineTo(x+380,y-120);

    ctx.stroke();

    ctx.beginPath();

    ctx.moveTo(x+160,y-160);
    // right
    ctx.lineTo(x+340,y-160);

    ctx.stroke();
    ctx.closePath();

    ctx.beginPath();

    ctx.moveTo(x+200,y-200);
    // right
    ctx.lineTo(x+300,y-200);

    ctx.stroke();
    ctx.closePath();
}

function DrawWindow(ctx, x, y) {
    ctx.fillStyle = 'rgb(255, 255, 55)';

    ctx.fillRect(x, y, 80, 100);
    ctx.clearRect(x+10,y+10,60,80);
    ctx.strokeRect(x+10,y+10,60,80);

    ctx.fillStyle = 'rgb(210,180,140)';
    ctx.fillRect(x+10, y+35, 60, 10);
    ctx.strokeRect(x+10, y+35, 60, 10);

    ctx.fillRect(x+35, y+45, 10, 45);
    ctx.strokeRect(x+35, y+45, 10, 45);
}

function DrawChimney(ctx, x, y) {
    ctx.beginPath();

    ctx.moveTo(x, y);
    // up
    ctx.lineTo(x, y-60);
    // right
    ctx.lineTo(x+30,y-60);
    // down
    ctx.lineTo(x+30,y-30);
    // left
    ctx.lineTo(x, y);
    ctx.stroke();
    // металлический 
    ctx.fillStyle = 'rgb(165,165,165)';

    ctx.fill();
}

function DrawLogCabin(ctx, x, y) {
    ctx.fillStyle = 'rgb(131,77,24)';

    ctx.fillRect(x, y, 460, 300);
    ctx.strokeRect(x, y, 460, 300);
}

function DrawDoor(ctx, x, y) {
    ctx.fillStyle = 'rgb(255,255,0)';

    ctx.fillRect(x, y, 140, 220);
    ctx.strokeRect(x, y, 140, 220); 

    ctx.clearRect(x+10, y+10, 120, 200);
    ctx.strokeRect(x+10, y+10, 120, 200);
    ctx.beginPath();
    ctx.arc(x+105,y+80,8,0,Math.PI*2,true);
    
    ctx.fillStyle = 'rgb(145,0,0)';
    ctx.stroke();
    ctx.fill();
}

function DrawPicketFence(ctx, x, y) {
    ctx.beginPath();

    ctx.moveTo(x, y);
    // up
    ctx.lineTo(x, y-150);
    // semicircle
    ctx.arc(x+16, y-150, 16, 0, Math.PI, true);
    // right
    ctx.lineTo(x+32, y-150);
    // up
    ctx.lineTo(x+32, y);
    ctx.lineTo(x, y);
    
    ctx.fillStyle = 'rgb(139,0,0)';
    ctx.fill();
}

function DrawFence(ctx, x, y) {
    for(let i=0; i < 1190;i+=34)
    {
        DrawPicketFence(ctx, x+i,y);
    }
}

function DrawHouse() {
    var canvas = document.getElementById("canvas");
    if (canvas.getContext) {
        var ctx = canvas.getContext("2d");
        DrawRoof(ctx, 600, 300);
        DrawWindow(ctx, 810, 140);
        DrawChimney(ctx, 761, 140);
        DrawLogCabin(ctx, 620, 301);
        DrawDoor(ctx, 720, 381);
        DrawWindow(ctx, 930, 400);
        DrawFence(ctx, 100, 670);
    }
}