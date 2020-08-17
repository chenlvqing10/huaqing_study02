drop table admin_info;

/*==============================================================*/
/* Table: admin_info                                            */
/*==============================================================*/
create table admin_info (
admin_no varchar(10) not null,
admin_name varchar(12) not null,
admin_gender varchar(2) not null,
admin_age integer not null,
college_no varchar(4) not null,
user_no varchar(7),
primary key (admin_no)
);

comment on table admin_info is
'管理员信息表';

alter table admin_info
   add foreign key FK_ADMI_REFE_COLL (college_no)
      references college_info (college_no)
      on delete restrict;

alter table admin_info
   add foreign key FK_ADMI_REFE_USER (user_no)
      references user_info (user_no)
      on delete restrict;
