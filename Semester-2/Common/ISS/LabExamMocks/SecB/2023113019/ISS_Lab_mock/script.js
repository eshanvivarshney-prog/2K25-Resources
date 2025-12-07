function callFn(){

    const element = document.getElementById("menu");
    
    // element.scrollIntoView();
    // element.scrollIntoView(false);
    // element.scrollIntoView({ block: "end" });
    element.scrollIntoView({ behavior: "smooth", block: "end", inline: "nearest" });
}

function sub(){
    var name=document.getElementsById("nameId");
    console.log(name)
    console.log(document.getElementsByName("emailId"))
    console.log(document.getElementsByName("messageId"))

}