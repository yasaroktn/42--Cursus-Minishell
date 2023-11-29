/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokten <yokten@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:04:54 by yokten            #+#    #+#             */
/*   Updated: 2023/11/29 11:44:10 by yokten           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_termios(void) {
    struct termios termios_p;

    if (tcgetattr(0, &termios_p) != 0)
        perror("Minishell: tcgetattr");
    termios_p.c_lflag &= ~ECHOCTL;
    if (tcsetattr(0, 0, &termios_p) != 0)
        perror("Minishell: tcsetattr");
}

void signal_handler(int sig) {
    if (sig == SIGINT) {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

static void handle_sigquit(int sig) {
    (void)sig;
    rl_redisplay();
}

void init_signal(void) {
    ft_termios();
    signal(SIGINT, (void (*)(int))signal_handler); // Cast is used to avoid a warning
    signal(SIGQUIT, (void (*)(int))handle_sigquit); // Cast is used to avoid a warning
}
