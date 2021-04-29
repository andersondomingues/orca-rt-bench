int: num_packets;
int: num_links;
int: hyperperiod_length;

set of int: PACKETS = 1..num_packets;
set of int: LINKS = 1..num_links;

array[LINKS, PACKETS] of int: deadline;    % maximum "end" execution time
array[LINKS, PACKETS] of int: min_start;   % prevents packet overleap
array[LINKS, PACKETS] of int: occupancy;   % time taken per link

array[LINKS, PACKETS] of var int: release_time; % problem's answer

% definition of overleap
predicate nonoverlap(
  var int:release1, var int:end1, var int:release2, var int:end2)
   = release1 + end1 <= end2 \/ release2 + end2 <= release1;

% prevent two flow from sharing the same resource at the same time
constraint forall(p1, p2 in PACKETS, l in LINKS where p1 < p2)(
    nonoverlap(
      release_time[l, p1],
      release_time[l, p1] + occupancy[l, p1], 
      release_time[l, p2],
      release_time[l, p2] + occupancy[l, p2]));

% release time occur after the beggining of period
constraint forall(l in LINKS, p in PACKETS)
  (release_time[l, p] >= min_start[l, p]);
  
% task must end before its deadline
constraint forall(l in LINKS, p in PACKETS)
  (release_time[l, p] + occupancy[l, p] <= deadline[l, p]);

% % optimization config., reduces hyper-period lenght
% var 0..hyperperiod_length: makespan = max(j in PACKETS)(release_time[j,num_links] + occupancy[j,num_links]);

% solve :: int_search([release_time[p,l] | p in PACKETS, l in LINKS], 
%   input_order, indomain_min, complete)
%   minimize makespan; 

solve satisfy;

/*
int: maxt = sum(j in PACKETS, t in OCCUPANCIES)(d[j,t]);

% performs tasks in a job in order
constraint forall(j in PACKETS, t in 1..(num_links-1))
  (s[j,t] + d[j,t] <= s[j,t+1]);

constraint forall(j1, j2 in PACKETS, t1, t2 in OCCUPANCIES 
  where j1 < j2 /\ mc[j1,t1] = mc[j2,t2])(
    nonoverlap(s[j1,t1],d[j1,t1], s[j2,t2],d[j2,t2]));

array[PACKETS, OCCUPANCIES] of var 0..maxt: s; % start time


predicate nonoverlap(var int:s1, var int:d1,
                     var int:s2, var int:d2)=
          s1 + d1 <= s2 \/ s2 + d2 <= s1;

var 0..maxt: makespan = max(j in PACKETS)(s[j,num_links] + d[j,num_links]);

solve :: int_search([s[j,t] | j in PACKETS, t in OCCUPANCIES], 
  input_order, indomain_min, complete)
  minimize makespan;

output [ show_int(3,s[j,t]) ++ if t = num_links then "\n" else " " endif 
  | j in PACKETS, t in OCCUPANCIES]; 

*/

