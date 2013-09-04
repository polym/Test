set sw=4 ts=4 nobk ai cin nu
let &termencoding=&encoding
set fileencodings=utf-8,gbk
set guioptions-=T
set guioptions-=m
au GUIENTER * simalt ~x
syn on
colo smyck
cd ~
map <F5> :! g++ %<.cpp -DLOCAL -Wall -o %<<CR>
map <F6> :! %< < %<.in > %<.out<CR>
set gfn=Courier_New:h12
map <F3> :bel vsplit %<.in <cr>
map <F4> :bel split %<.out <cr>
map <F2> <Esc>ggdG:call Template()<cr>39Go
imap <F2> <Esc><F2>
map <F1> : cd ACM <cr>
func Template()
let l=0
let l=l+1 | call setline(l, '/*************************************************************************')
let l=l+1 | call setline(l, "Author: zjut_polym") 
let l=l+1 | call setline(l, "Created Time:   ".strftime("%c")) 
let l=l+1 | call setline(l, "File Name: ".expand("%"))
let l=l+1 | call setline(l, '************************************************************************/')
let l=l+1 | call setline(l, '#include <iostream>')
let l=l+1 | call setline(l, "#include <cstdio>")
let l=l+1 | call setline(l, "#include <cstring>")
let l=l+1 | call setline(l, "#include <cmath>")
let l=l+1 | call setline(l, "#include <cstdlib>")
let l=l+1 | call setline(l, "#include <algorithm>")
let l=l+1 | call setline(l, "#include <vector>")
let l=l+1 | call setline(l, "#include <set>")
let l=l+1 | call setline(l, "#include <map>")
let l=l+1 | call setline(l, "#include <string>")
let l=l+1 | call setline(l, "#include <climits>")
let l=l+1 | call setline(l, "#include <queue>")
let l=l+1 | call setline(l, "using namespace std;")
let l=l+1 | call setline(l, "")
let l=l+1 | call setline(l, "")
let l=l+1 | call setline(l, "\//----------------------[ZJUT-polym for div2]-------------------------------------")
let l=l+1 | call setline(l, "#define ll long long") 
let l=l+1 | call setline(l, "#define MOD 1000000007")
let l=l+1 | call setline(l, "#define PII pair<int, int>")
let l=l+1 | call setline(l, "#define ff first")
let l=l+1 | call setline(l, "#define ss second")
let l=l+1 | call setline(l, "#define sz(v) (int)v.size()")
let l=l+1 | call setline(l, "#define _mst(buf, val) memset(buf, val, sizeof(buf))")
let l=l+1 | call setline(l, "#define rep(i, l, r) for(i = (l); i <= (r); i++)")
let l=l+1 | call setline(l, "#define srep(i, l, r) for(i = (l); i >= (r); i--)")
let l=l+1 | call setline(l, "#define repi(it, c) for(typeof(c.begin())it = c.begin(); it != c.end(); it++)")
let l=l+1 | call setline(l, "#define inf 0x3f3f3f3f")
let l=l+1 | call setline(l, "#define N 100005")
let l=l+1 | call setline(l, "#define eps 1e-8")
let l=l+1 | call setline(l, "#define pi (2.0 * acos(0.0))")
let l=l+1 | call setline(l, "\//--------------------------------------------------------------------------------")
let l=l+1 | call setline(l, "")
let l=l+1 | call setline(l, "")
let l=l+1 | call setline(l, "int main() {")
let l=l+1 | call setline(l, "    return 0;")
let l=l+1 | call setline(l, "}")
let l=l+1 | call setline(l, "") 
endfunc
