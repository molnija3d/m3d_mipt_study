call plug#begin()

Plug 'jpalardy/vim-slime'
Plug 'rking/ag.vim'
Plug 'kien/ctrlp.vim'
Plug 'tpope/vim-sensible'
Plug 'jiangmiao/auto-pairs'
Plug 'preservim/nerdtree'
Plug 'morhetz/gruvbox'
Plug 'ycm-core/YouCompleteMe'
Plug 'easymotion/vim-easymotion'

call plug#end()

let g:termdebug_wide=1
let g:slime_target = "tmux"
colorscheme gruvbox
set background=dark
set number
nmap <F8> :TagbarToggle<CR>
set expandtab
set incsearch
set mouse=a
syntax on
packadd termdebug

nnoremap <C-n> :NERDTreeToggle<CR>
map <Leader> <Plug>(easymotion-prefix)

map <F3> :%!astyle<CR>
map <silent> <C-h> :call WinMove('h')<CR>
map <silent> <C-j> :call WinMove('j')<CR>
map <silent> <C-k> :call WinMove('k')<CR>
map <silent> <C-l> :call WinMove('l')<CR>

function! WinMove(key)
 let t:curwin = winnr()
 exec "wincmd ".a:key
 if(t:curwin == winnr())
   if(match(a:key,'[jk]'))
     wincmd v
   else
     wincmd s
   endif
   exec "wincmd ".a:key
 endif
endfunction
