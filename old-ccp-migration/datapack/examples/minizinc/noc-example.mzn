int: num_packets;
int: num_links;
int: hyperperiod_length;

set of int: PACKETS = 1..num_packets;
set of int: LINKS = 1..num_links;

array[LINKS, PACKETS] of int: deadline;    % maximum "end" execution time
array[LINKS, PACKETS] of int: min_start;   % prevents packet overleap
array[LINKS, PACKETS] of int: occupancy;   % time taken per link

array[LINKS, PACKETS] of var int: release_time;  % answer

% cannot release packets before their release time
constraint forall(l in LINKS, p in PACKETS)(
    release_time[l, p] >= min_start[l, p]
);
  
% packet must be transmitted before its deadline
constraint forall(l in LINKS, p in PACKETS)(
  if deadline[l, p] > -1 then  % eliminate sparse matrix problem
    release_time[l, p] + occupancy[l, p] <= deadline[l, p] 
  endif
);
  
% force all links to be allocated during the same time slice
% assumption: the whole channel is allocated during the whole transmission
% replacement: link allocation time is T' = T + 4, link close time is unknown
constraint forall(l1, l2 in LINKS, p in PACKETS)(
  if deadline[l1, p] > -1 /\ deadline[l2, p] > -1 then
    release_time[l1, p] = release_time[l2, p]
  endif
);

% definition of overleap predicate (same as in job shop)
predicate nonoverlap(
  var int:b1, var int:e1, var int:b2, var int:e2)
   = b1 + e1 <= b2 \/ b2 + e2 <= b1;

% prevent two flow from sharing the same resource at the same time
% (uses the predicate above)
constraint forall(p1, p2 in PACKETS, l in LINKS where p1 < p2)(
  if deadline[l, p1] > -1 /\ deadline[l, p2] > -1 then
    nonoverlap(
      release_time[l, p1], occupancy[l, p1] , 
      release_time[l, p2], occupancy[l, p2] )
  endif
);

solve satisfy;

output [show_int(2, release_time[l,p]) ++ if p = num_packets then "\n" else " " endif | l in LINKS, p in PACKETS]; 


