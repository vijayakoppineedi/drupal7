/**
 * @file
 * Disabling dropdowns main menu parent link
 * 
 */
 
(function(jQuery) {
  Drupal.behaviors.custom_i5k_transcript = {
    attach: function (context, settings) {
      jQuery('.menuparent > ul').prev('a').click(function(e) {    
        //e.preventDefault()
        return false;
      }); 
	  /*Outboundlinks.js  code below*/
      var filetypes = /\.(zip|exe|dmg|pdf|doc.*|xls.*|ppt.*|mp3|txt|rar|wma|mov|avi|wmv|flv|wav)$/i;
      var baseHref = '';
      if (jQuery('base').attr('href') != undefined) baseHref = jQuery('base').attr('href'); 
	  
	  jQuery('a').live('click', function(event) {	
	    //alert("in live ");
        var el = jQuery(this);
        var track = true;
        var href = (typeof(el.attr('href')) != 'undefined' ) ? el.attr('href') :"";
        var isThisDomain = href.match(document.domain.split('.').reverse()[1] + '.' + document.domain.split('.').reverse()[0]);
        if (!href.match(/^javascript:/i)) {
          var elEv = []; elEv.value=0, elEv.non_i=false;
          if (href.match(/^mailto\:/i)) {
            elEv.category = "Email";
            elEv.action = "click";
            elEv.label = href.replace(/^mailto\:/i, '');
            elEv.loc = href;
          }
          else if (href.match(filetypes)) {
            var extension = (/[.]/.exec(href)) ? /[^.]+$/.exec(href) : undefined;
            elEv.category = "Download";
            elEv.action = "click-" + extension[0];
            elEv.label = href.replace(/ /g,"-");
            elEv.loc = baseHref + href;
          }
          else if (href.match(/^https?\:/i) && !isThisDomain) {
		    //alert(" hello in external links ");
            elEv.category = "External";
            elEv.action = "click";
            elEv.label = href.replace(/^https?\:\/\//i, '');
            elEv.non_i = true;
            elEv.loc = href;
          }        
          else track = false;
 
          if (track) {
		   //alert("in track ");
            if ( el.attr('target') == undefined || el.attr('target').toLowerCase() != '_blank') {
		      //alert("in if ");
		      _gaq.push(['_trackEvent', elEv.category.toLowerCase(), elEv.action.toLowerCase(), elEv.label.toLowerCase(), elEv.value, elEv.non_i]);
              setTimeout(function() { location.href = elEv.loc; }, 400);
              return false;
            } else if(el.attr('target').toLowerCase() == '_blank') {
		  	  //alert("in track in target new "+el.attr('target')+ " loca "+elEv.loc);
		      _gaq.push(['_trackEvent', elEv.category.toLowerCase(), elEv.action.toLowerCase(), elEv.label.toLowerCase(), elEv.value, elEv.non_i]);
			  location.href = elEv.loc;
		      setTimeout('window.open(' + location.href + ')', 100) 
			  return false; 
		    }
          }
        }
      });  
	  
	  jQuery(".emailLnk a").live('click',function(e){	 	 
	    // Getting anchor tag id value which is community_id
	    var community_id = jQuery(this).attr('id')
	    // splitting the id(ex: emailLnk-85492D0)
	    var split_cid =  community_id.split("-");
	    //split_cid[1] is 85492D0
	    var url ='/community_contact/'+split_cid[1];	  
	    jQuery.ajax({url: url, success: function(data) {              
	      window.location.href = "mailto:"+data;
        }
        });  //AJAX closing braces			
      });	  
	  
    } 
  }
});