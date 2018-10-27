/**
 * Stop an iframe or HTML5 <video> from playing
 * @param  {Element} element The element that contains the video
 */
var iframe = document.querySelector( 'iframe');
var video = document.querySelector( 'video' );
if ( iframe ) {
	var iframeSrc = iframe.src;
	iframe.src = iframeSrc;
}
if ( video ) {
	video.pause();
}