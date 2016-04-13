(function(jQuery) {
  Drupal.behaviors.custom_i5k_transcript = {
    attach: function (context, settings) {	  
	  var $table = jQuery('table.tripal-chado_feature-contents-table');
	  var $wrap = jQuery('<div/>').attr('id', 'popup-window');
	  $table.append(
       jQuery('td.tripal-contents-table-td-data').append($wrap)
	  ); 
      var parentDivs = jQuery('#multiAccordion div'),
    childDivs = jQuery('#multiAccordion h3').siblings('div');	
    jQuery("#multiAccordion h2").first().removeClass().addClass('accordionOpen');
    jQuery("#multiAccordion div").first().show();
	jQuery("#multiAccordion h3").first().removeClass().addClass('accordionOpen');
    jQuery("#multiAccordion div div").first().show();
		
    jQuery('#multiAccordion > h2').click(function () {
      //parentDivs.slideUp();
	  //alert("h2 "+jQuery(this).first().next().first().first().html());
      if (jQuery(this).next().is(':hidden')) {	   
	    //jQuery("#multiAccordion h2").removeClass().addClass('accordionClose');
	    jQuery(this).removeClass().addClass('accordionOpen');	
        jQuery(this).next().slideDown();		
      } else {	
	    jQuery(this).removeClass().addClass('accordionClose');				
        jQuery(this).next().slideUp();	  
      }
    });  
    jQuery('#multiAccordion h3').click(function () {
      //childDivs.slideUp();
      if (jQuery(this).next().is(':hidden')) {
	    //jQuery("#multiAccordion h3").removeClass().addClass('accordionClose');
	    jQuery(this).removeClass().addClass('accordionOpen');		
        jQuery(this).next().slideDown();
      } else {
	    jQuery(this).removeClass().addClass('accordionClose');
        jQuery(this).next().slideUp();
      }
    });		
  }
};
})(jQuery);
;
/**
 * @file
 * jQuery code.
 * 
 */

// Setting up popup.
// 0 means disabled; 1 means enabled.
var popupStatus = 0;

/**
 * Loading popup with jQuery.
 */
function popup_message_load_popup() {
  // Loads popup only if it is disabled.
  if (popupStatus == 0) {
    jQuery("#popup-message-background").css( {
      "opacity": "0.7"
    });
    jQuery("#popup-message-background").fadeIn("slow");
    jQuery("#popup-message-window").fadeIn("slow");
    popupStatus = 1;
  }
}

/**
 * Disabling popup with jQuery.
 */
function popup_message_disable_popup() {
  // Disables popup only if it is enabled.
  if (popupStatus == 1) {
    jQuery("#popup-message-background").fadeOut("slow");
    jQuery("#popup-message-window").fadeOut("slow");
    popupStatus = 0;
  }
}

/**
 * Centering popup.
 */
function popup_message_center_popup(width, height) {
  // Request data for centering.
  var windowWidth = document.documentElement.clientWidth;
  var windowHeight = document.documentElement.clientHeight;

  var popupWidth = 0
  if (typeof width == "undefined") {
    popupWidth = jQuery("#popup-message-window").width();
  }
  else {
    popupWidth = width;
  }
  var popupHeight = 0
  if (typeof width == "undefined") {
    popupHeight = jQuery("#popup-message-window").height();
  }
  else {
    popupHeight = height;
  }

  // Centering.
  jQuery("#popup-message-window").css( {
    "position": "absolute",
    "width" : popupWidth + "px",
    "height" : popupHeight + "px"
  });

  // Only need force for IE6.
  jQuery("#popup-message-background").css( {
    "height": windowHeight
  });
}

/**
 * Display popup message.
 */
function popup_message_display_popup(fid, type, width, height, unspliced, strand, fmin, fmax) {
  fmin = (typeof fmin === "undefined") ? "":fmin;
  fmax = (typeof fmax === "undefined") ? "":fmax;
  strand = (strand === '-1') ? "negative":strand;
  
  unspliced = (typeof unspliced === "undefined") ? "0" : unspliced;
  var popup_title = "";
  if(fmin && fmax) {  
    popup_title = (unspliced == '1')?(fid+"-"+type+"-"+strand+"-"+unspliced):(fid+"-"+type+"-"+strand+"-"+unspliced+"-"+fmin+"-"+fmax);	  	
  } else {
    popup_title = (unspliced == '1')?(fid+"-"+type+"-"+strand+"-"+unspliced):(fid+"-"+type+"-"+strand);	  
  }
  jQuery.ajax({
    type: 'POST',
    url: '/zclip/'+popup_title,        
    data: '',		
    success: function(data) { 	 
      jQuery('#popup-window').append(data);	
      // Loading popup.
	  
      popup_message_center_popup(width, height);
      popup_message_load_popup();
    jQuery(".l-region--navigation").css({"display":"none"});
	
      // Closing popup.
      // Click the x event!
      jQuery("#popup-message-close").click(function() {
        jQuery('#popup-window').text('');
        popup_message_disable_popup();
	    jQuery(".l-region--navigation a:visited").css({"background":"none"}); 
	    jQuery(".l-region--navigation").css({"display":"block"});
      });
      // Click out event!
      jQuery("#popup-message-background").click(function() {
        jQuery('#popup-window').text('');
        popup_message_disable_popup();
	    jQuery(".l-region--navigation a:visited").css({"background":"none"});
	    jQuery(".l-region--navigation").css({"display":"block"});
      });
      // Press Escape event!
      jQuery(document).keydown(function(e) {	  
      if (e.keyCode == 27 && popupStatus == 1) {
	    jQuery('#popup-window').text('');
        popup_message_disable_popup();	  
	    jQuery(".l-region--navigation a:visited").css({"background":"none"});
        jQuery(".l-region--navigation").css({"display":"block"});
	  }
    });    		  
    },
    error: function(){ alert("ERROR"); },            
    cache:false
  });
}
;
(function ($) {

Drupal.googleanalytics = {};

$(document).ready(function() {

  // Attach mousedown, keyup, touchstart events to document only and catch
  // clicks on all elements.
  $(document.body).bind("mousedown keyup touchstart", function(event) {

    // Catch the closest surrounding link of a clicked element.
    $(event.target).closest("a,area").each(function() {

      // Is the clicked URL internal?
      if (Drupal.googleanalytics.isInternal(this.href)) {
        // Skip 'click' tracking, if custom tracking events are bound.
        if ($(this).is('.colorbox')) {
          // Do nothing here. The custom event will handle all tracking.
          //console.info("Click on .colorbox item has been detected.");
        }
        // Is download tracking activated and the file extension configured for download tracking?
        else if (Drupal.settings.googleanalytics.trackDownload && Drupal.googleanalytics.isDownload(this.href)) {
          // Download link clicked.
          ga("send", "event", "Downloads", Drupal.googleanalytics.getDownloadExtension(this.href).toUpperCase(), Drupal.googleanalytics.getPageUrl(this.href));
        }
        else if (Drupal.googleanalytics.isInternalSpecial(this.href)) {
          // Keep the internal URL for Google Analytics website overlay intact.
          ga("send", "pageview", { "page": Drupal.googleanalytics.getPageUrl(this.href) });
        }
      }
      else {
        if (Drupal.settings.googleanalytics.trackMailto && $(this).is("a[href^='mailto:'],area[href^='mailto:']")) {
          // Mailto link clicked.
          ga("send", "event", "Mails", "Click", this.href.substring(7));
        }
        else if (Drupal.settings.googleanalytics.trackOutbound && this.href.match(/^\w+:\/\//i)) {
          if (Drupal.settings.googleanalytics.trackDomainMode != 2 || (Drupal.settings.googleanalytics.trackDomainMode == 2 && !Drupal.googleanalytics.isCrossDomain(this.hostname, Drupal.settings.googleanalytics.trackCrossDomains))) {
            // External link clicked / No top-level cross domain clicked.
            ga("send", "event", "Outbound links", "Click", this.href);
          }
        }
      }
    });
  });

  // Track hash changes as unique pageviews, if this option has been enabled.
  if (Drupal.settings.googleanalytics.trackUrlFragments) {
    window.onhashchange = function() {
      ga('send', 'pageview', location.pathname + location.search + location.hash);
    }
  }

  // Colorbox: This event triggers when the transition has completed and the
  // newly loaded content has been revealed.
  $(document).bind("cbox_complete", function () {
    var href = $.colorbox.element().attr("href");
    if (href) {
      ga("send", "pageview", { "page": Drupal.googleanalytics.getPageUrl(href) });
    }
  });

});

/**
 * Check whether the hostname is part of the cross domains or not.
 *
 * @param string hostname
 *   The hostname of the clicked URL.
 * @param array crossDomains
 *   All cross domain hostnames as JS array.
 *
 * @return boolean
 */
Drupal.googleanalytics.isCrossDomain = function (hostname, crossDomains) {
  /**
   * jQuery < 1.6.3 bug: $.inArray crushes IE6 and Chrome if second argument is
   * `null` or `undefined`, http://bugs.jquery.com/ticket/10076,
   * https://github.com/jquery/jquery/commit/a839af034db2bd934e4d4fa6758a3fed8de74174
   *
   * @todo: Remove/Refactor in D8
   */
  if (!crossDomains) {
    return false;
  }
  else {
    return $.inArray(hostname, crossDomains) > -1 ? true : false;
  }
};

/**
 * Check whether this is a download URL or not.
 *
 * @param string url
 *   The web url to check.
 *
 * @return boolean
 */
Drupal.googleanalytics.isDownload = function (url) {
  var isDownload = new RegExp("\\.(" + Drupal.settings.googleanalytics.trackDownloadExtensions + ")([\?#].*)?$", "i");
  return isDownload.test(url);
};

/**
 * Check whether this is an absolute internal URL or not.
 *
 * @param string url
 *   The web url to check.
 *
 * @return boolean
 */
Drupal.googleanalytics.isInternal = function (url) {
  var isInternal = new RegExp("^(https?):\/\/" + window.location.host, "i");
  return isInternal.test(url);
};

/**
 * Check whether this is a special URL or not.
 *
 * URL types:
 *  - gotwo.module /go/* links.
 *
 * @param string url
 *   The web url to check.
 *
 * @return boolean
 */
Drupal.googleanalytics.isInternalSpecial = function (url) {
  var isInternalSpecial = new RegExp("(\/go\/.*)$", "i");
  return isInternalSpecial.test(url);
};

/**
 * Extract the relative internal URL from an absolute internal URL.
 *
 * Examples:
 * - http://mydomain.com/node/1 -> /node/1
 * - http://example.com/foo/bar -> http://example.com/foo/bar
 *
 * @param string url
 *   The web url to check.
 *
 * @return string
 *   Internal website URL
 */
Drupal.googleanalytics.getPageUrl = function (url) {
  var extractInternalUrl = new RegExp("^(https?):\/\/" + window.location.host, "i");
  return url.replace(extractInternalUrl, '');
};

/**
 * Extract the download file extension from the URL.
 *
 * @param string url
 *   The web url to check.
 *
 * @return string
 *   The file extension of the passed url. e.g. "zip", "txt"
 */
Drupal.googleanalytics.getDownloadExtension = function (url) {
  var extractDownloadextension = new RegExp("\\.(" + Drupal.settings.googleanalytics.trackDownloadExtensions + ")([\?#].*)?$", "i");
  var extension = extractDownloadextension.exec(url);
  return (extension === null) ? '' : extension[1];
};

})(jQuery);
;
