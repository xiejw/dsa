package main

import (
	"fmt"
)

const (
	Size  = 9
	Debug = true
)

type Problem []int

func main() {
	problem := Problem{
		0, 0, 3, 0, 1, 0, 0, 0, 0,
		4, 1, 5, 0, 0, 0, 0, 9, 0,
		2, 0, 6, 5, 0, 0, 3, 0, 0,

		5, 0, 0, 0, 8, 0, 0, 0, 9,
		0, 7, 0, 9, 0, 0, 0, 3, 2,
		0, 3, 8, 0, 0, 4, 0, 6, 0,

		0, 0, 0, 2, 6, 0, 4, 0, 3,
		0, 0, 0, 3, 0, 0, 0, 0, 8,
		3, 2, 0, 0, 0, 7, 9, 5, 0,
	}

	problem.Print()
	problem.SearchOptions()
}

//   int options_count = searchOptions(problem);
//
//   {
//     dlNodet* top_row = dlCreate(4 * Size * Size);
//     for (int i = 0; i < 4 * Size * Size; i++) {
//       dlCreateNode(top_row, NULL, NULL);
//     }
//
//     // hides all items in table already.
//     int hidden_items_count = 0;
//     int p, r, c, b;
//     for (int x = 0; x < Size; x++) {
//       int offset = x * Size;
//       for (int y = 0; y < Size; y++) {
//         int k = problem[offset + y];
//         if (k == 0) continue;
//
//         getItemId(x, y, k, &p, &r, &c, &b);
//         dlHideNode(top_row, p);
//         dlHideNode(top_row, r);
//         dlHideNode(top_row, c);
//         dlHideNode(top_row, b);
//         hidden_items_count += 4;
//       }
//     }
//
//     int item_count = 4 * Size * Size - hidden_items_count;
//
//     if (DEBUG) {
//       int count = 0;
//       p         = 0;
//       while (1) {
//         p = (top_row + p)->rlink;
//         if (p == 0) {
//           break;
//         }
//         count++;
//       }
//       assert(item_count == count);
//       fmt.Printf("total items before searching: %d\n", count);
//     }
//
//     // header
//     // all items
//     // first spacer
//     // 1 spacers + 4 items for each option.
//     dancingNodet* opt_row =
//         malloc((1 + item_count + 1 + ((1 + 4) * options_count)) *
//                sizeof(dancingNodet));
//     int opt_count = 0;
//
//     opt_row[0].id = 0;  // unused.
//     opt_count++;
//
//     {
//       p = 0;
//       while (1) {
//         p = (top_row + p)->rlink;
//         if (p == 0) {
//           break;
//         }
//         int opt_id          = opt_count;  // 1-based.
//         top_row[p].id       = opt_id;
//         dancingNodet* opt_p = opt_row + opt_id;
//         opt_p->len          = 0;
//         opt_p->id           = opt_id;  // self
//         opt_p->ulink        = opt_id;  // self
//         opt_p->dlink        = opt_id;  // self
//         opt_count++;
//       }
//     }
//
//     // first spacer.
//
//     int spacer_count   = 0;
//     int last_spacer_id = opt_count;
//
//     {
//       // ulink unused, rlink will be set later.
//       dancingNodet* opt_p = opt_row + last_spacer_id;
//       opt_p->id           = last_spacer_id;
//       opt_p->top          = 0;
//       opt_count++;
//       spacer_count++;
//     }
//
//     free(opt_row);
//     dlFree(top_row);
//   }
//
//   // debugDoubleLinks();
//
//   return 0;
// }

// -----------------------------------------------------------------------------
// Problem.
// -----------------------------------------------------------------------------

// Prints the Soduku Problem on screen.
func (p Problem) Print() {
	// header
	fmt.Printf("+-----+-----+-----+\n")
	for x := 0; x < Size; x++ {
		offset := x * Size
		fmt.Printf("|")
		for y := 0; y < Size; y++ {
			num := p[offset+y]
			if num == 0 {
				fmt.Printf(" ")
			} else {
				fmt.Printf("%d", p[offset+y])
			}

			if (y+1)%3 != 0 {
				fmt.Printf(" ")
			} else {
				fmt.Printf("|")
			}
		}
		fmt.Printf("\n")
		if (x+1)%3 == 0 {
			fmt.Printf("+-----+-----+-----+\n")
		}
	}
}

// Seach all options that on (x,y) the digit k is allowed to be put there.
func (p Problem) SearchOptions() int {
	total := 0
	if Debug {
		fmt.Printf("total 10 options:\n")
	}

	for x := 0; x < Size; x++ {
		offset := x * Size

		for y := 0; y < Size; y++ {
			if p[offset+y] > 0 {
				continue // prefilled.
			}

			box_x := (x / 3) * 3
			box_y := (y / 3) * 3

			for k := 1; k <= Size; k++ {
				// search row
				for j := 0; j < Size; j++ {
					if p[j+offset] == k {
						goto not_a_option
					}
				}
				// search column
				for j := 0; j < Size; j++ {
					if p[j*Size+y] == k {
						goto not_a_option
					}
				}

				// search box. static unroll
				if p[(box_x*Size+box_y)] == k ||
					p[(box_x*Size+box_y+1)] == k ||
					p[(box_x*Size+box_y+2)] == k ||
					p[((box_x+1)*Size+box_y)] == k ||
					p[((box_x+1)*Size+box_y+1)] == k ||
					p[((box_x+1)*Size+box_y+2)] == k ||
					p[((box_x+2)*Size+box_y)] == k ||
					p[((box_x+2)*Size+box_y+1)] == k ||
					p[((box_x+2)*Size+box_y+2)] == k {
					goto not_a_option
				}

				total++
				if Debug && total < 20 {
					fmt.Printf("  x %d, y %d, k %d\n", x, y, k)
				}
			not_a_option:
			}
		}
	}
	if Debug {
		fmt.Printf("in total %d options\n", total)
	}
	return total
}

//
// // p{i,j}, r{i,k} c{j,k} b{x,k}  x=3 * floor(i/3) + floor(j/3)
// //
// // 1-based
// void getItemId(int i, int j, int k, int* p, int* r, int* c, int* b) {
//   int x      = 3 * (i / 3) + (j / 3);
//   int offset = 0;
//
//   k = k - 1;  // k is 1 based.
//
//   *p = i * Size + j + offset + 1;  // item id is 1 based.
//   offset += Size * Size;
//
//   *r = i * Size + k + offset + 1;  // item id is 1 based.
//   offset += Size * Size;
//
//   *c = j * Size + k + offset + 1;  // item id is 1 based.
//   offset += Size * Size;
//
//   *b = x * Size + k + offset + 1;  // item id is 1 based.
// }
//
// // Debugging only
// void debugDoubleLinks() {
//   dlNodet* h = dlCreate(8);
//
// #define PRINT_HEADER(h) fmt.Printf("header l %d r %d\n", h->llink, h->rlink)
// #define PRINT_NODE(h, id)                                             \
//   fmt.Printf("%6d l %d r %d  %s\n", id, (h + id)->llink, (h + id)->rlink, \
//          (h + id)->data);
//
//   int id1 = dlCreateNode(h, "a", DL_NO_FREE);
//   assert(id1 == 1);
//   PRINT_HEADER(h);
//   PRINT_NODE(h, 1);
//
//   int id2 = dlCreateNode(h, "b", DL_NO_FREE);
//   assert(id2 == 2);
//   PRINT_HEADER(h);
//   PRINT_NODE(h, 1);
//   PRINT_NODE(h, 2);
//
//   int id3 = dlCreateNode(h, "c", DL_NO_FREE);
//   assert(id3 == 3);
//   PRINT_HEADER(h);
//   PRINT_NODE(h, 1);
//   PRINT_NODE(h, 2);
//   PRINT_NODE(h, 3);
//
//   dlHideNode(h, 2);
//   PRINT_HEADER(h);
//   PRINT_NODE(h, 1);
//   PRINT_NODE(h, 2);
//   PRINT_NODE(h, 3);
//
//   dlFree(h);
// }
