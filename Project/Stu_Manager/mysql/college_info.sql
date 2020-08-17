drop table college_info;

/*==============================================================*/
/* Table: college_info                                          */
/*==============================================================*/
create table college_info (
college_no varchar(4) not null,
college_name varchar(20) not null,
primary key (college_no)
);

comment on table college_info is
'学院信息表';
