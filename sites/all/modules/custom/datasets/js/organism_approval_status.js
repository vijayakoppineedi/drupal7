
function statusClick(status, organism) {
  if(status == 0) {
     res = confirm('Are you sure you want to reject the '+organism+'  organism. This will delete records from node, node_revision, chado_organism and chado.organism table.');
     return true;
  }
  return false;
}
