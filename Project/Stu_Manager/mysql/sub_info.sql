drop table sub_info;

/*==============================================================*/
/* Table: sub_info                                              */
/*==============================================================*/
create table sub_info (
sub_no varchar(4) not null,
sub_name varchar(20) not null,
profs_no varchar(4) not null,
primary key (sub_no)
);

comment on table sub_info is
'专业科目表';

alter table sub_info
   add foreign key FK_SUB__REFE_PROF (profs_no)
      references profs_info (profs_no)
      on delete restrict;
