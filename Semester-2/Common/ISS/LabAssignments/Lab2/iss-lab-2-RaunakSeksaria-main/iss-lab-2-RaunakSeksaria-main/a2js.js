var format = 12;

setInterval(updateClock, 1000);
// clearInterval(interval);
function updateClock() {
    const d = new Date();
    let x = document.getElementById('clock');
    // x.innerHTML = d.toISOString().slice(0,10);
    if(format==24)
    x.innerHTML = (d.getHours()<10? "0" + d.getHours() : d.getHours() )+":"+ (d.getMinutes()<10?"0" + d.getMinutes() : d.getMinutes())+ ":" + (d.getSeconds()<10? "0" + d.getSeconds():d.getSeconds());
    else if(format==12){
        var hours = d.getHours();
        // var hours = 13;
        var minutes = d.getMinutes();
        var sec = d.getSeconds();
        var ampm = hours >= 12? "PM" : "AM"; 
        if(hours >12) //there is no 0, only 12, in this format
        hours-=12;
        if(hours==0)
        hours = 12;
        x.innerHTML =  (hours <10?"0"+ hours:""+ hours)+ ":"+ (minutes<10?"0" + minutes: ""+ minutes) + ":" + (sec <10?"0"+sec:""+sec) +" "+ ampm; 
    }
}
var click = true;
function setFormat(){
    if(click==true)
    format = 12;
    else
    format = 24;
    click = !click;
}