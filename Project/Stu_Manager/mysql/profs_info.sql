drop table profs_info;

/*==============================================================*/
/* Table: profs_info                                            */
/*==============================================================*/
create table profs_info (
profs_no varchar(4) not null,
profs_name varchar(20) not null,
college_no varchar(4) not null,
primary key (profs_no)
);

comment on table profs_info is
'专业信息表';

alter table profs_info
   add foreign key FK_PROF_REFE_COLL (college_no)
      references college_info (college_no)
      on delete restrict;
