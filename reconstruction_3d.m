clear;
clc;

ax=importdata("demo.csv");

n=ax(:,1);
x=ax(:,2);
y=ax(:,3);

m=1563;

phi=n./m*pi;
theta=atan(0);
d=x.*cos(theta)-y.*sin(theta);

xx=x-(1-cos(phi)).*d*cos(theta);
yy=(1-cos(phi)).*d*sin(theta)+y;
zz=d.*sin(phi);

axis_new=[xx yy zz];

recons=pointCloud(axis_new);
pcshow(recons);
pcwrite(recons,"recons2c.pcd");
