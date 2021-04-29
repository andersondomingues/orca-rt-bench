int: nc = 3;     % number of colours

var 1..nc: wa;   % each state can be of any color
var 1..nc: nt;
var 1..nc: nsw;
var 1..nc: v;
var 1..nc: sa;
var 1..nc: t;
var 1..nc: q;

constraint wa != nt;
constraint wa != sa;
constraint nt != sa;
constraint nt != q;
constraint sa != q;
constraint sa != v;
constraint q != nsw;
constraint nsw != v;

solve satisfy;

output ["wa=\(wa)\t nt=\(nt)\t sa=\(sa)\n",
        "q=\(q)\t nsw=\(nsw)\t v=\(v)\n",
         "t=", show(t),  "\n"];