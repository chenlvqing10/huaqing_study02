drop table stu_sub;

/*==============================================================*/
/* Table: stu_sub                                               */
/*==============================================================*/
create table stu_sub (
stu_no varchar(10) not null,
stu_year_no varchar(6) not null,
stu_sub_no1 varchar(4) not null,
stu_sub_no2 varchar(4) not null,
stu_sub_no3 varchar(4) not null,
stu_sub_no4 varchar(4),
stu_sub_no5 varchar(4),
stu_sub_no6 varchar(4),
stu_sub_no7 varchar(4),
stu_sub_no8 varchar(4),
stu_sub_no9 varchar(4),
stu_sub_no10 varchar(4),
stu_sub_no11 varchar(4),
stu_sub_no12 varchar(4),
college_no varchar(4) not null,
profs_no varchar(4) not null,
primary key (stu_no)
);

comment on table stu_sub is
'学生学期科目表
stu_sub
相同学院相同专业相同学期的学生科目表应该相同，需要修改所以不应该包含学号
由管理员增删改查
由学生 查询本学期的科目情况
至少三个科目
至多12个科目';


alter table stu_sub
   add foreign key FK_STU__REFE_YEAR (stu_year_no)
      references year_info (stu_year_no)
      on delete restrict;

alter table stu_sub
   add foreign key FK_STU__REFE_COLL (college_no)
      references college_info (college_no)
      on delete restrict;

alter table stu_sub
   add foreign key FK_STU__REFE_PROF (profs_no)
      references profs_info (profs_no)
      on delete restrict;
