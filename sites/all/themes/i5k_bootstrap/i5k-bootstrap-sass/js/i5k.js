(function ($) {
  $(document).ready(function() {
    $('#base').parent().addClass('active');
    
    $('.form-type-select').addClass('clearfix');
    
    $('#tripal-chado_feature-contents-table').find('.tripal_toc_list_item_link').click(function() {
       $('.tripal_toc_list_item_link').parent().removeClass('active');
       $(this).parent().addClass('active');
    });

    var txAreaWidth = $('.resizable-textarea').find('textarea').outerWidth();	
    $('.resizable-textarea').find('.grippie').css("width", txAreaWidth).animate({marginLeft: '+=2px'}, 0);;
       

    $(window).resize(function() {
    	var newtxAreaWidth = $('.resizable-textarea').find('textarea').outerWidth();
	$('.resizable-textarea').find('.grippie').css("width", newtxAreaWidth);
    	
    	var windowsize = $(window).width();
	if (windowsize < 655){
    	    $('.resizable-textarea').find('.grippie').css("marginLeft", "0");
        } else if  (windowsize > 656){
	    $('.resizable-textarea').find('.grippie').css("marginLeft", "163.2px");

        }; 
    });
  });
}(jQuery));

