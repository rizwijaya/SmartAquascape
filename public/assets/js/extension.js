// brightness
function fun(e) {
    var kontener = document.getElementById('kontener');
    var val = e.value;
    kontener.setAttribute("style", "filter: brightness(" + val + "%);");
}
// brightness