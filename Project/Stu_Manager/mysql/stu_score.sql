drop table stu_score;

/*==============================================================*/
/* Table: stu_score                                             */
/*==============================================================*/
create table stu_score (
stu_no varchar(10) not null,
stu_year_no varchar(6) not null,
sub_no1_sc int(3) not null,
sub_no2_sc int(3) not null,
sub_no3_sc int(3) not null,
sub_no4_sc int(3),
sub_no5_sc int(3),
sub_no6_sc int(3),
sub_no7_sc int(3),
sub_no8_sc int(3),
sub_no9_sc int(3),
sub_no10_sc int(3),
sub_no11_sc int(3),
sub_no12_sc int(3),
college_no varchar(4) not null,
profs_no varchar(4) not null,
primary key (stu_no)
);

comment on table stu_score is
'学生学期成绩表
stu_score
每个学生的成绩是不同
设定了学生学期科目表之后
通过学院编号，专业编号，学期编号得到该学生本学期的科目，然后设置这些科目的成绩';

alter table stu_score
   add foreign key FK_STU__REFE_YEAR (stu_year_no)
      references year_info (stu_year_no)
      on delete restrict;

alter table stu_score
   add foreign key FK_STU__REFE_COLL (college_no)
      references college_info (college_no)
      on delete restrict;


alter table stu_score
   add foreign key FK_STU__REFE_PROF (profs_no)
      references profs_info (profs_no)
      on delete restrict;
