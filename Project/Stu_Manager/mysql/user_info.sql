drop table user_info;

/*==============================================================*/
/* Table: user_info                                             */
/*==============================================================*/
create table user_info (
user_no varchar(7) not null,
username varchar(12) not null,
passwd varchar(10) not null,
usertype integer not null,
primary key (user_no)
);

comment on table user_info is
'用户信息表';
