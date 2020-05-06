" =================================================================================================
"                            Boubacar DIENE<boubacar.diene@gmail.com>
" =================================================================================================
"
" - :sp                     --> Split horizontally
" - :vsp                    --> Split vertically
" - :e <file>               --> Replace current content with <file>
" - :e!                     --> Reload currently opened file (useful if modified elsewhere)
" - :help <keyword>         --> Keyword can be a command (sp, vsp, tag, ...)
"
" - :tag <keyword>          --> Search for an existing tag
" - :ts                     --> show tags list
" - Ctrl+T                  --> Stop ctags search
" - Ctrl+AltGR+]            --> (Ctrl-]). Cursor in a function then this will take you there
"
" - Ctrl+P                  --> Search file or directory using CtrlP plugin
" - Ctrl+O                  --> Leave CtrlP
"
" - vim <dir>               --> Open NERDTree and browse <dir> content
" - :NERDTree <dir>         --> To browse <dir> content (CtrlP possible in opened view)
" - Ctrl+O                  --> Back to previous file
" - q                       --> Quit NERDTree
" - :NERDTreeFind           --> Find the currently active file in the filesystem
" - :NERDTreeRefreshRoot    --> Refresh root
"
" - Ctrl+W                  --> Switch between windows (x2 to make it work?)
" - :tabe %                 --> Pop out a new tab temporarily
" - :q                      --> Back to the splitted windows
"
" - v                       --> Enter VISUAL mode (Esc to go back to normal mode)
" - V                       --> Enter VISUAL LINE mode (Esc to go back to normal mode)
" - y                       --> Copy selected text (still in visual mode)
" - p                       --> Paste selected text (still in visual mode)
" - <N>j                    --> Select the <N>th lines in VISUAL mode
"
" - :sh                     --> Start the shell
" - exit                    --> Back to vim (from the shell)
"
" - :set <cmd>!             --> Undo cmd (example: set number! will remove numbers)
"
" - :u                      --> Undo
" - Ctrl+R                  --> Redo
"
" - G                       --> Go to end of file (<N>G possible with N >= 1)
" - gg                      --> Go to beginning of file
" - $                       --> Go to end of line
"
" - :grep                   --> Search in all files (standard grep command)
" - :cw                     --> Show the "location list" to see result
"
" - v + select text + y     --> Visual mode, select text then "y" to yank into register 0
" - /Ctrl+R then 0          --> Search selected text in current file
"
" - :%s/from/to/g           --> Find "from" and replace it with "to" in the whole file
"
" - :set syntax=whitespace  --> Show tabs in green and spaces in red
"
" - shift + >               --> Shift right (In normal mode)
" - <                       --> Shift left (In normal mode)
"
" =================================================================================================
" pathogen.vim makes it super easy to install plugins and runtime files in their
" own private directories (See https://github.com/tpope/vim-pathogen)
" =================================================================================================
execute pathogen#infect()
syntax on
filetype plugin indent on

" =================================================================================================
" Indentation: Tab replaced with 4 spaces
" =================================================================================================
set tabstop=4 softtabstop=0 expandtab shiftwidth=4 smarttab

" =================================================================================================
" - Show line numbers
" - Show column numbers
" - Ignore case
" - Highlight search
" - Show match (brackets, ...)
" - Show (partial) command in the last line of the screen
" - Minimal number of screen lines to keep above and below the cursor
" - Line position tracking
" - Remove the underline
" - Line number in blue
" =================================================================================================
"set number
set ignorecase
set hlsearch
set showmatch
set showcmd
set scrolloff=5
set cursorline
set paste
set ruler
highlight clear CursorLine
highlight CursorLineNR ctermbg=blue

" =================================================================================================
" CtrlP: See http://kien.github.io/ctrlp.vim/#installation
" =================================================================================================
set runtimepath^=~/.vim/bundle/ctrlp.vim
