namespace PAW_S04
{
	partial class Form2
	{
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing && (components != null))
			{
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent()
		{
			this.components = new System.ComponentModel.Container();
			this.textBox1 = new System.Windows.Forms.TextBox();
			this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
			this.salvareFisierTextToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.citireFisierTextToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.serializareToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.deserializareToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
			this.contextMenuStrip1.SuspendLayout();
			this.SuspendLayout();
			// 
			// textBox1
			// 
			this.textBox1.ContextMenuStrip = this.contextMenuStrip1;
			this.textBox1.Dock = System.Windows.Forms.DockStyle.Fill;
			this.textBox1.Location = new System.Drawing.Point(0, 0);
			this.textBox1.Multiline = true;
			this.textBox1.Name = "textBox1";
			this.textBox1.Size = new System.Drawing.Size(800, 450);
			this.textBox1.TabIndex = 0;
			// 
			// contextMenuStrip1
			// 
			this.contextMenuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.salvareFisierTextToolStripMenuItem,
            this.citireFisierTextToolStripMenuItem,
            this.serializareToolStripMenuItem,
            this.deserializareToolStripMenuItem});
			this.contextMenuStrip1.Name = "contextMenuStrip1";
			this.contextMenuStrip1.Size = new System.Drawing.Size(181, 114);
			// 
			// salvareFisierTextToolStripMenuItem
			// 
			this.salvareFisierTextToolStripMenuItem.Name = "salvareFisierTextToolStripMenuItem";
			this.salvareFisierTextToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
			this.salvareFisierTextToolStripMenuItem.Text = "Salvare Fisier Text";
			this.salvareFisierTextToolStripMenuItem.Click += new System.EventHandler(this.salvareFisierTextToolStripMenuItem_Click);
			// 
			// citireFisierTextToolStripMenuItem
			// 
			this.citireFisierTextToolStripMenuItem.Name = "citireFisierTextToolStripMenuItem";
			this.citireFisierTextToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
			this.citireFisierTextToolStripMenuItem.Text = "Citire Fisier Text";
			this.citireFisierTextToolStripMenuItem.Click += new System.EventHandler(this.citireFisierTextToolStripMenuItem_Click);
			// 
			// serializareToolStripMenuItem
			// 
			this.serializareToolStripMenuItem.Name = "serializareToolStripMenuItem";
			this.serializareToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
			this.serializareToolStripMenuItem.Text = "Serializare";
			this.serializareToolStripMenuItem.Click += new System.EventHandler(this.serializareToolStripMenuItem_Click);
			// 
			// deserializareToolStripMenuItem
			// 
			this.deserializareToolStripMenuItem.Name = "deserializareToolStripMenuItem";
			this.deserializareToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
			this.deserializareToolStripMenuItem.Text = "Deserializare";
			this.deserializareToolStripMenuItem.Click += new System.EventHandler(this.deserializareToolStripMenuItem_Click);
			// 
			// Form2
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(800, 450);
			this.Controls.Add(this.textBox1);
			this.Name = "Form2";
			this.Text = "Form2";
			this.contextMenuStrip1.ResumeLayout(false);
			this.ResumeLayout(false);
			this.PerformLayout();

		}

		#endregion

		private System.Windows.Forms.TextBox textBox1;
		private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
		private System.Windows.Forms.ToolStripMenuItem salvareFisierTextToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem citireFisierTextToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem serializareToolStripMenuItem;
		private System.Windows.Forms.ToolStripMenuItem deserializareToolStripMenuItem;
	}
}