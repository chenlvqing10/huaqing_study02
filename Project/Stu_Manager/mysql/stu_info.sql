drop table stu_info;

/*==============================================================*/
/* Table: stu_info                                              */
/*==============================================================*/
create table stu_info (
stu_no varchar(10) not null,
stu_name varchar(12) not null,
stu_gender varchar(4) not null,
stu_age integer not null,
stu_grade integer not null,
stu_class integer not null,
college_no varchar(4) not null,
profs_no varchar(4) not null,
user_no varchar(7),
primary key (stu_no)
);

comment on table stu_info is
'学生基本信息表';

alter table stu_info
   add foreign key FK_STU__REFE_COLL (college_no)
      references college_info (college_no)
      on delete restrict;

alter table stu_info
   add foreign key FK_STU__REFE_PROF (profs_no)
      references profs_info (profs_no)
      on delete restrict;

alter table stu_info
   add foreign key FK_STU__REFE_USER (user_no)
      references user_info (user_no)
      on delete restrict;
