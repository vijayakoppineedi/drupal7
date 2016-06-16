Files to copy:
1. Applied patch to captcha.module file due to erro "CAPTCHA session reuse attack detected"

https://www.drupal.org/files/issues/1395184_31.patch

create table public.ds_cordinator_organism(id bigserial primary key,
							     genus varchar(20) NOT NULL,
								 species varchar(20) NOT NULL,
								 common_name varchar(20) NOT NULL,
								 taxid integer NOT NULL,
								 cordinator_name varchar(20) NOT NULL,
								 email varchar(254) NOT NULL,
								 comments text,
								 status smallint NOT NULL default 2,
								 created integer default 0,
								 UNIQUE(taxid)
								 );
								 
create table public.ds_request_project(id bigserial primary key,
                                       uid integer DEFAULT 0 NOT NULL,
                                       genus text NOT NULL,
                                       species text NOT NULL,
				       ncbi_taxid integer NOT NULL,
				       common_name text NOT NULL,
                                       genome_assembly_hosted text NOT NULL,
                                       is_ncbi_submitted varchar(20) NOT NULL,
                                       is_assembly varchar(20) NOT NULL,
                                       involved_in_generation varchar(20) NOT NULL,
				       description text NOT NULL,
                                       fullname varchar(254) NOT NULL,
				       email varchar(254) NOT NULL,
                                       
                                       status smallint NOT NULL default 2,
                                       created integer default 0
                                      );

create table public.ds_organism_assembly(oa_id bigserial primary key,
        uid integer DEFAULT 0 NOT NULL,
	name varchar(254) NOT NULL,
  	email varchar(254) NOT NULL,
	organism varchar(128) NOT NULL,
	common_name varchar(128) NOT NULL,
        description text,
        organism_image_url varchar(254),
	is_curate_assembly varchar(20) NOT NULL,
	is_same integer,
	manual_curation_name varchar(254),
        manual_curation_email varchar(254),
	need_assistance varchar(20),
	reason varchar(254),
	time_from integer default 0,
	time_to integer default 0,
	assembly_name varchar(254) NOT NULL,
	assembly_version varchar(254) NOT NULL,
	assembly_accession varchar(254) NOT NULL,
	assembly_method varchar(254) NOT NULL,
	is_publish varchar(20) NOT NULL,
	publish_field_data varchar(254),
	other_notes text,
	geo_location varchar(254),
	tissues_located varchar(254),
	gender varchar(20),
	other_gender varchar(60),
	data_source_strain varchar(254),
	data_source_notes text,
	data_source_seqplatform varchar(254),
	data_source_url varchar(254),
        filename text NOT NULL,
        md5sum text NOT NULL,
        created integer default 0	
);
							  

CREATE SEQUENCE public.gene_prediction_pid_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;

create table public.ds_gene_prediction(
  pid integer PRIMARY KEY DEFAULT nextval('gene_prediction_pid_seq'::regclass),
  uid integer DEFAULT 0 NOT NULL,
  organism varchar(128) NOT NULL,
  program varchar(254) NOT NULL,
  version varchar(124) NOT NULL,
  additional_info text,
  other_methods text,
  name varchar(254) NOT NULL,
  email varchar(254) NOT NULL,
  affiliation varchar(254) NOT NULL,
  gene_name varchar(254) NOT NULL,
  gene_version varchar(254) NOT NULL,
  descriptive_track varchar(254) NOT NULL,
  is_ogs varchar(124) NOT NULL,
  reason varchar(254),
  is_publish varchar(20) NOT NULL,
  publish_field_data varchar(254),
  is_download varchar(124),
  filename text NOT NULL,
  md5sum text NOT NULL,
  created integer default 0	
);		

CREATE SEQUENCE mapped_dataset_id_seq
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
	
create table public.ds_mapped_dataset(
  id integer PRIMARY KEY DEFAULT nextval('mapped_dataset_id_seq'::regclass),
  uid integer DEFAULT 0 NOT NULL,
  organism varchar(128) NOT NULL,
  name varchar(254) NOT NULL,
  email varchar(254) NOT NULL,
  affiliation varchar(254) NOT NULL,
  geo_location varchar(254),
  tissues_located varchar(254),
  gender varchar(20),
  other_gender varchar(60),
  sequence_platform varchar(254),
  is_publish varchar(20) NOT NULL,
  publish_field_data varchar(254),
  descriptive_track varchar(254) NOT NULL,
  data_source_url varchar(254),
  program varchar(254) NOT NULL,
  version varchar(124) NOT NULL,
  additional_info text,
  other_methods text,  
  filename text NOT NULL,
  md5sum text NOT NULL,
  created integer default 0	
);  
								 
Steps: for New Organism
1. Request new organism If its not there in dropdown
   To request go to url: http://domain_url/datasets/request-project
2. Once the user submitted the request organism, an email goes to administrator.
3. Administrator checks and sees if the organism is worth to approve/reject.
4. An email goes to the requested user about the organism approval if it is approved. If rejected he wont   receives and email.


Requirements:
1. Date module - install and enable it. dateapi and date_popup modules.
2. honeypot module - install and enable it.

3. create a "datasets" folder for organism image under sites/default/files/
4. create db_tables in databse.


















