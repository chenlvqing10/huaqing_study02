drop table stu_info_tmp;

/*==============================================================*/
/* Table: stu_info_tmp                                          */
/*==============================================================*/
create table stu_info_tmp (
stu_no varchar(10) not null,
stu_name varchar(12) not null,
stu_gender varchar(2) not null,
stu_age integer not null,
stu_grade integer not null,
stu_class integer not null,
college_no varchar(4) not null,
profs_no varchar(4) not null,
use_user_no varchar(7),
user_no varchar(4),
primary key (stu_no)
);

alter table stu_info_tmp
   add foreign key FK_STU__REFE_USER (use_user_no)
      references user_info (user_no)
      on delete restrict;

alter table stu_info_tmp
   add foreign key FK_STU__REFE_PROF (profs_no)
      references profs_info (profs_no)
      on delete restrict;

alter table stu_info_tmp
   add foreign key FK_STU__REFE_COLL (college_no)
      references college_info (college_no)
      on delete restrict;
