function scopeHandle(object)
{
var temp="d"+object.id;
var div = document.getElementById(temp);
var button = document.getElementById(object.id);
if(div.style.display != 'none'){
	 div.style.display = 'none';
button.value = '+';
}
 else {
div.style.display = 'inline';
button.value = '-';
}};