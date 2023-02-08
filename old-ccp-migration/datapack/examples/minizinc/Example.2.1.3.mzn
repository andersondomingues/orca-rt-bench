int: flour;
int: banana;
int: sugar;
int: butter;
int: cocoa;

constraint assert(flour >= 0, "<flour> must be a non-negative value");
constraint assert(banana >= 0, "<banana> must be a non-negative value");
constraint assert(sugar >= 0, "<sugar> must be a non-negative value");
constraint assert(butter >= 0, "<butter> must be a non-negative value");
constraint assert(cocoa >= 0, "<cocoa> must be a non-negative value");

var 0..100: b;
var 0..100: c;

constraint 250 * b + 200 * c <= flour;
constraint 2 * b  <= banana;
constraint 75 * b + 150 * c <= sugar;
constraint 100 * b + 150 * c <= butter;
constraint 75 * c <= cocoa;

solve maximize 400 * b + 450 * c;

