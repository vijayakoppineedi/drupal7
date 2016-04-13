jQuery(function() {
  jQuery("#edit-organism").change(function() {
     var organism = jQuery(this).val(); // get selected value
     if (organism == 'New Organism') { // require a URL
       window.open("/datasets/request-project","_blank"); // redirect
     }
     return false;
  })
});
